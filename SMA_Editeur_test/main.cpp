#include "main.hpp"

int hauteur_ = 400;
int largeur_ = 400;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.setBackgroundBrush(QBrush(QColor(255,255,255)));
    scene.setSceneRect(QRect(0,0,largeur_ + 100,hauteur_ + 100));
    scene.addRect(QRect(50,50,largeur_,hauteur_), QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

    creer_limites(&scene);

    Editeur map(&scene);
    map.cartographier();

    // Appel de la vue

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QBrush(QColor(220,220,220)));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Test d'algo"));
    view.show();

    return app.exec();
}

QPointF reverseCoord( const QPointF & p)
{
    return QPointF( p.y(), p.x() );
}

void ajouterTL(std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > & pq, const QPointF& TL_1, const QPointF& TL_2, const qreal& testCoord)
{
    if(TL_1.x() == testCoord)
        pq.push(TL_1.y());

    if(TL_2.x() == testCoord)
        pq.push(TL_2.y());
}

void construire1mur(QGraphicsScene * scene,
                    const int& nbPorte,
                    const QPointF & depart,
                    const QPointF & arrivee,
                    const QPointF & inter_1_1,
                    const QPointF & inter_1_2,
                    const QPointF & inter_2_1,
                    const QPointF & inter_2_2)
{
   switch(nbPorte)
   {
       case 0:
           scene->addItem(new Mur(depart, arrivee));
       break;

       case 1:
       {
           scene->addItem(new Mur(depart, inter_1_1));
           scene->addItem(new Mur(inter_1_2, arrivee));
       }
       break;

       case 2:
       {
           scene->addItem(new Mur(depart, inter_1_1));
           scene->addItem(new Mur(inter_1_2, inter_2_1));
           scene->addItem(new Mur(inter_2_2, arrivee));
       }
       break;
   }
}
void creer_limites(QGraphicsScene * scene)
{
    srand(time(0));

    Porte* porte_1 = new Porte();
    Porte* porte_2 = 0;
    scene->addItem(porte_1);
    porte_1->positionnerPorte();

    qreal p1x = porte_1->boundingRect().topLeft().x();
    qreal p1y = porte_1->boundingRect().topLeft().y();

    bool sempiete;

    do{
        sempiete = false;
        porte_2 = new Porte();
        scene->addItem(porte_2);
        porte_2->positionnerPorte();

        qreal p2x = porte_2->boundingRect().topLeft().x();
        qreal p2y = porte_2->boundingRect().topLeft().y();

        if((p1y == p2y && abs(p1x - p2x) < 40)
               || (p1x == p2x && abs(p1y - p2x) < 40 ))
        {
            delete porte_2;
            sempiete = true;
        }

    } while ( sempiete );

    creer_murs(scene, porte_1->boundingRect().topLeft(), porte_2->boundingRect().topLeft());
}

void creer_murs(QGraphicsScene * scene, const QPointF& TL_1, const QPointF& TL_2)
{
    qreal x_mur_gauche = 49;
    qreal x_mur_droite = scene->width() - 50;
    qreal y_mur_haut = 49;
    qreal y_mur_bas = scene->height() - 50;

    qreal taille_porte = 30;

    QPointF depart;
    QPointF arrivee;
    QPointF inter_1_1;
    QPointF inter_1_2;
    QPointF inter_2_1;
    QPointF inter_2_2;

    int nbPorte;

    for( int i = 0; i < 4; ++i )
    {
        std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > coordonnees;

        switch(i)
        {
            case 0 : // Mur de droite
                depart = QPointF(x_mur_droite, 50);
                arrivee = QPointF(x_mur_droite + 1, y_mur_bas);

                ajouterTL(coordonnees, TL_1, TL_2, x_mur_droite);
                nbPorte = coordonnees.size();

                if(nbPorte > 0)
                {
                    inter_1_1 = QPointF(x_mur_droite + 1, coordonnees.top());
                    inter_1_2 = QPointF(x_mur_droite, coordonnees.top() + taille_porte);

                    if( nbPorte == 2)
                    {
                        coordonnees.pop();
                        inter_2_1 = QPointF(x_mur_droite + 1, coordonnees.top());
                        inter_2_2 = QPointF(x_mur_droite, coordonnees.top() + taille_porte);
                    }
                }
                break;

            case 1 : // Mur du bas

                depart = QPointF(50, y_mur_bas);
                arrivee = QPointF(x_mur_droite, y_mur_bas + 1);

                ajouterTL(coordonnees, reverseCoord(TL_1), reverseCoord(TL_2), y_mur_bas);
                nbPorte = coordonnees.size();

                if(nbPorte > 0)
                {
                    inter_1_1 = QPointF(coordonnees.top(), y_mur_bas + 1);
                    inter_1_2 = QPointF(coordonnees.top() + taille_porte, y_mur_bas );

                    if( nbPorte == 2)
                    {
                        coordonnees.pop();
                        inter_2_1 = QPointF(coordonnees.top(), y_mur_bas + 1);
                        inter_2_2 = QPointF(coordonnees.top() + taille_porte, y_mur_bas );
                    }
                }
                break;

            case 2 : // Mur de gauche

                depart = QPointF(x_mur_gauche, 50);
                arrivee = QPointF(x_mur_gauche + 1, y_mur_bas);

                ajouterTL(coordonnees, TL_1, TL_2, x_mur_gauche);
                nbPorte = coordonnees.size();

                if(nbPorte > 0)
                {
                    inter_1_1 = QPointF(x_mur_gauche + 1, coordonnees.top());
                    inter_1_2 = QPointF(x_mur_gauche, coordonnees.top() + taille_porte);

                    if( nbPorte == 2)
                    {
                        coordonnees.pop();
                        inter_2_1 = QPointF(x_mur_gauche + 1, coordonnees.top());
                        inter_2_2 = QPointF(x_mur_gauche, coordonnees.top() + taille_porte);
                    }
                }
                break;

            case 3 : // Mur du haut

                depart = QPointF(50, y_mur_haut);
                arrivee = QPointF(x_mur_droite, y_mur_haut + 1);

                ajouterTL(coordonnees, reverseCoord(TL_1), reverseCoord(TL_2), y_mur_haut);
                nbPorte = coordonnees.size();

                if(nbPorte > 0)
                {
                    inter_1_1 = QPointF(coordonnees.top(), y_mur_haut + 1);
                    inter_1_2 = QPointF(coordonnees.top() + taille_porte, y_mur_haut );

                    if( nbPorte == 2)
                    {
                        coordonnees.pop();
                        inter_2_1 = QPointF(coordonnees.top(), y_mur_haut + 1);
                        inter_2_2 = QPointF(coordonnees.top() + taille_porte, y_mur_haut );
                    }
                }
                break;
        }

        construire1mur(scene, nbPorte, depart, arrivee, inter_1_1, inter_1_2, inter_2_1, inter_2_2);

    }
}

QTextStream& operator<<( QTextStream& o, const QGraphicsItem * pQGI)
{
     QString s = typeid(*pQGI).name();
     s = s.toUpper();
     s = s.remove(0, 6);
     o << s << "\nTL " << pQGI->boundingRect().topLeft().x() << " " << pQGI->boundingRect().topLeft().y()
      <<"\nBR " <<  pQGI->boundingRect().bottomRight().x() << " " <<  pQGI->boundingRect().bottomRight().y() << "\n\n";

    return o;
}
