#include "parser.h"
#include "main.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    matInt grille;

    QGraphicsScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.setBackgroundBrush(QBrush(QColor(255,255,255)));

    try
    {
        parser("./Carte_Niveau.txt", &scene, grille);
    }
    catch( const std::exception &e)
    {
        QMessageBox::critical(NULL, "Fichier non trouvé", e.what());
    }

    foreach( std::vector<int> line, grille)
    {
        foreach( int elem, line )
            std::cout << elem << "|" ;

        std::cout << std::endl;
    }

    std::cout << grille.size() << std::endl ;

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QBrush(QColor(220,220,220)));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Test parser"));
    view.show();

    return a.exec();
}


void parser(const QString & filename, QGraphicsScene * scene, matInt &grille )
{
    ParserFactory factory;

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception("Le fichier spécifié n'existe pas");

    QTextStream flux(&file);
    QString s;
    QStringList ssplit;

    flux.setCodec("UTF-8");

    int hauteur, largeur;

    s = flux.readLine();
    ssplit = s.split(" ");
    largeur = ssplit[1].toInt() ;

    s = flux.readLine();
    ssplit = s.split(" ");
    hauteur = ssplit[1].toInt() ;

    hauteur -= 2 ;
    largeur -= 2 ;

    scene->setSceneRect(QRect(0,0,largeur + 100,hauteur + 100));
    scene->addRect(QRect(50,50,largeur,hauteur), QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

    s = flux.readLine();

    while( s != QString("DATA"))
    {
        QPointF limits [2];

        while( (s = flux.readLine()) == QString("MUR"))
        {
            QString type (s[0]);
            type += s.remove(0, 1).toLower();

            for(int i = 0 ; i < 2 ; ++i)
            {
                s = flux.readLine();
                ssplit = s.split(" ");
                limits[ i ] = QPointF((qreal)ssplit[1].toInt(), (qreal)ssplit[2].toInt());
            }

            flux.readLine();

            scene->addItem(factory.instancierItem(type, limits[0], limits[1] ));
        }
    }

    while(! flux.atEnd())
    {
        s = flux.readLine();
        ssplit = s.split("|");
        ssplit.pop_back();

        std::vector<int> temp ;
        foreach ( QString s, ssplit )
        {
            temp.push_back( s.toInt());
        }

        grille.push_back( temp );
    }

    file.close();
}
