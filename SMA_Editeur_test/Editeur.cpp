#include "Editeur.hpp"

Editeur::Editeur(const QGraphicsScene * scene) : scene_(scene)
{
    width_ = (int) scene->width(); width_ -= 100;
    height_ = (int) scene->height(); height_ -= 100;

    elemSize_ = width_ + 2 ;

    grille_ = std::vector<Pixel>( elemSize_ * (height_ + 2));

    for( std::vector<Pixel>::iterator it = grille_.begin() ; it != grille_.end() ; ++it)
    {
        it->niveau = -1;
        it->coul = BLANC;
    }
}

void Editeur::cartographier()
{
    std::vector<QPointF> liste_initiale;
    std::vector<QPointF> a_traiter;

    QList<QGraphicsItem *> liste_item = scene_->items();
    liste_item.pop_front(); // on enlève la salle

    /* 2 portes */

    for( int i = 0 ; i < 2 ; ++i )
    {
        QPointF TL = liste_item[i]->boundingRect().topLeft();
        QPointF BR = liste_item[i]->boundingRect().bottomRight();

        if(BR.x() - TL.x() == 1)
        {
            // porte verticale
            for( qreal var = TL.y(); var < BR.y(); ++var )
            {
                // on rajoute chaque point de la porte dans la liste
                liste_initiale.push_back(QPointF(TL.x(), var));
            }
        }
        else
        {
            // porte horizontale
            for( qreal var = TL.x(); var < BR.x(); ++var )
            {
                // on rajoute chaque point de la porte dans la liste
                liste_initiale.push_back(QPointF(var, TL.y()));
            }
        }
    }

    liste_item.pop_front(); // on enlève la porte 1
    liste_item.pop_front(); // on enlève la porte 2

    int niveau = 0;

    while(!liste_initiale.empty())
    {
        for(std::vector<QPointF>::iterator it = liste_initiale.begin(); it != liste_initiale.end(); ++it)
        {
            int indice = (int) it->x() - 49 + elemSize_ * ( (int) it->y() - 49 ) ;
            //std::cout << " indice : " << indice << std::endl;
            grille_[ indice ].niveau = niveau;
            grille_[ indice ].coul = NOIR;
        }

        for(std::vector<QPointF>::iterator it = liste_initiale.begin(); it != liste_initiale.end(); ++it)
        {
            int itX = (int) it->x() - 49 ;
            int itY = (int) it->y() - 49 ;

            int indiceHaut = itX + elemSize_ * ( itY - 1 );
            int indiceBas = itX + elemSize_ * ( itY + 1 ) ;
            int indiceGauche = (itX - 1) + elemSize_ * itY ;
            int indiceDroite = (itX + 1) + elemSize_ * itY ;

            QPointF ptAjout;

            if( itY - 1 > 0 && grille_[ indiceHaut ].coul == BLANC )
            {
                ptAjout = QPointF(it->x(), it->y() - 1);

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceHaut ].coul = GRIS;
                }
            }

            if( itY + 1 < height_ + 2 && grille_[ indiceBas ].coul == BLANC )
            {
                ptAjout = QPointF(it->x(), it->y() + 1);

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceBas ].coul = GRIS;
                }
            }

            if( itX + 1 < elemSize_ && grille_[ indiceDroite ].coul == BLANC )
            {
                ptAjout = QPointF(it->x() + 1, it->y());

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceDroite ].coul = GRIS;
                }
            }

            if( itX - 1 > 0 && grille_[ indiceGauche ].coul == BLANC )
            {
                ptAjout = QPointF(it->x() - 1, it->y());

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceGauche ].coul = GRIS;
                }
            }
        }

        liste_initiale.clear();
        liste_initiale = a_traiter;

        a_traiter.clear();

        ++niveau;
    }

    sauver_grille();
}

bool Editeur::verifier_traitement(const QList<QGraphicsItem*>& liste_item, const QPointF & point)
{
    bool retour = false;
    bool contenu = false;

    foreach(QGraphicsItem * item, liste_item)
    {
        if(item->contains(point) )
        {
            contenu = true;
            break;
        }
    }

    if(contenu == false)
        retour = true;


    return retour;
}

void Editeur::sauver_grille()
{
    QFile file("./Carte_Niveau.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cout << "Erreur d'ouverture du fichier" << std::endl ;
        return;
    }

    QTextStream flux(&file);

    flux.setCodec("UTF-8");

    // Dimensions de la pièce (murs compris)
    flux << "WIDTH " << width_ + 2 <<"\nHEIGHT " << height_ + 2 << "\n\n" ;

    QList<QGraphicsItem *> liste_item = scene_->items();

    //On enlève la salle et les portes
    for (int i = 0 ; i < 3 ; ++i)
        liste_item.pop_front();

    // Enregistrement de tous les objets
    for( int i = 0 ; i < liste_item.size() ; ++i )
        flux << liste_item[ i ] ;


    flux << "DATA\n" ;

    int compteur = 0 ;
    foreach( Pixel p, grille_ )
    {
        if(compteur == elemSize_)
        {
            flux << "\n" ;
            compteur = 0;
        }

        flux << p.niveau << "|";

        ++compteur;
    }

}
