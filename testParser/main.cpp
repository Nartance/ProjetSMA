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

    /*foreach( std::vector<int> line, grille)
    {
        foreach( int elem, line )
            std::cout << elem << "|" ;

        std::cout << std::endl;
    }

    std::cout << grille.size() << std::endl ;*/

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QBrush(QColor(220,220,220)));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Test parser"));
    view.show();

    return a.exec();
}


/*!
 * \fn  void parser(const QString & filename, QGraphicsScene * scene, matInt &grille )
 *
 * \brief Parse un fichier contenant toutes les données de la scène.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param filename ( Entrée ) Nom du fichier contenant les données.
 * \param scène ( Entrée / Sortie ) La scène recevant les éléments.
 * \param grille ( Entrée ) La map d'élévation.
 *
 */

void parser(const QString & filename, QGraphicsScene * scene, matInt &grille )
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception("Le fichier spécifié n'existe pas");

    QTextStream flux(&file);
    QString s;
    QStringList ssplit;

    flux.setCodec("UTF-8");

    int hauteur, largeur;

    // Début de la lecture du fichier : lecture de la largeur (murs compris)
    s = flux.readLine();
    ssplit = s.split(" ");
    largeur = ssplit[1].toInt() ;

    // Lecture de la hauteur de la scène (murs compris)
    s = flux.readLine();
    ssplit = s.split(" ");
    hauteur = ssplit[1].toInt() ;

    // On enlève les murs (épaisseur de 1)
    hauteur -= 2 ;
    largeur -= 2 ;

    // On crée la scène aux bonnes dimensions
    scene->setSceneRect(QRect(0,0,largeur + 100,hauteur + 100));
    scene->addRect(QRect(50,50,largeur,hauteur), QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

    // Saut de ligne
    s = flux.readLine();

    // Les points qui vont être lus
    QPointF limits [2];

    // Boucle de lecture des items
    while( (s = flux.readLine()) != QString("DATA"))
    {
        // Lecture du type d'item (en passant de TYPE à Type)
        QString type (s[0]);
        type += s.remove(0, 1).toLower();

        // Si c'est un mur, il faut lire deux points (topleft et bottomright). Sinon, il n'y a qu'un point à lire
        int nbPoint = 1;

        if( type == QString("Mur"))
            nbPoint = 2;

        // Lecture du ou des points
        for(int i = 0 ; i < nbPoint ; ++i)
        {
            // Stockage des points
            s = flux.readLine();
            ssplit = s.split(" ");
            limits[ i ] = QPointF((qreal)ssplit[1].toInt(), (qreal)ssplit[2].toInt());
        }

        // Saut de ligne
        flux.readLine();

        // Instanciation puis ajout de l'item lu dans la scène en utilisant l'usine parseur
        scene->addItem(ParserFactory::getInstance().instancierItem(type, limits[0], limits[1] ));
    }

    // Lecture des données de la map d'élévation
    while(! flux.atEnd())
    {
        // Lecture de la ligne
        s = flux.readLine();

        // Stockage des valeurs de la ligne
        ssplit = s.split("|");
        ssplit.pop_back();

        // Remplissage dans la grille
        std::vector<int> temp ;
        foreach ( QString s, ssplit )
        {
            temp.push_back( s.toInt());
        }

        grille.push_back( temp );
    }

    // Fermeture du fichier
    file.close();
}
