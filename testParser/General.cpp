#include "General.hpp"

qreal normalise_angle(qreal angle)
{
    while(angle < 0)
        angle += 360;
    while(angle > 360)
        angle -= 360;
    return angle;
}

QPoint change_repere(QPoint point)
{
    return QPoint(point.x() + 50, point.y() + 50);
}

void afficher_QPointF(QPointF point)
{
    std::cout << "(" << point.x() << ";" << point.y() << ")" << std::endl;
}

void afficher_QRectF(QRectF rect)
{
    std::cout << "TopLeft : ";
    afficher_QPointF(rect.topLeft());

    std::cout << "BottomRight : ";
    afficher_QPointF(rect.bottomRight());
}

/*
void lire(const QString & filename, QGraphicsScene * scene, matInt grille)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        // throw std::exception("Le fichier spécifié n'existe pas");
        std::cout << "ERROR" << std::endl;

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

            terrain_scene_->addItem(new Mur( limits[0], limits[1] ));
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
*/
