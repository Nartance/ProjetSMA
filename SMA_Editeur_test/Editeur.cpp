/*!
 * \file  "Editeur.cpp"
 *
 * \brief Fichier contenant la définition des méthodes de la classe réprésentant l'éditeur de la scène.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */

#include "Editeur.hpp"

/***************************************METHODES PRIVEES*********************************************************/

/*!
 * \fn  bool Editeur::verifier_traitement(const QList<QGraphicsItem*>& liste_item, const QPointF & point)
 *
 * \brief Retourne vrai si le point n'a pas été traité dans la cartographie.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param liste_item ( Entrée ) Liste des item déjà traité.
 * \param point ( Entrée ) Le point à tester.
 *
 * \return Vrai si aucun item de la scène ne contient le point à tester.
 */
bool Editeur::verifier_traitement(const QList<QGraphicsItem*>& liste_item, const QPointF & point)
{
    bool contenu = false;

    foreach(QGraphicsItem * item, liste_item)
    {
        if(item->contains(point) )
        {
            contenu = true;
            break;
        }
    }

    return !contenu;
}

/*!
 * \fn  void Editeur::sauver_grille()
 *
 * \brief Sauve les items et la grille d'élévation dans un fichier
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
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

/*!
 * \fn  QPointF Editeur::reverseCoord( const QPointF & p)
 *
 * \brief Inverse les coordonnées d'un point.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param p ( Entrée ) Le point à inverser.
 *
 * \return Le point inversé.
 */
QPointF Editeur::reverseCoord( const QPointF & p)
{
    return QPointF( p.y(), p.x() );
}

/*!
 * \fn  void Editeur::ajouterTL(std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > & pq, const QPointF& TL_1, const QPointF& TL_2, const qreal& testCoord)
 *
 * \brief Ajoute la coordonnée y des points dans la file de priorité si la coordonnée x correspond à une certaine valeur.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param pq ( Entrée / Sortie ) La file de priorité.
 * \param TL_1 ( Entrée ) Le premier point à tester.
 * \param TL_2 ( Entrée ) Le deuxième point à tester.
 * \param testCoord ( Entrée ) La coordonnée de comparaison.
 *
 */
void Editeur::ajouterTL(std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > & pq, const QPointF& TL_1, const QPointF& TL_2, const qreal& testCoord)
{
    if(TL_1.x() == testCoord)
        pq.push(TL_1.y());

    if(TL_2.x() == testCoord)
        pq.push(TL_2.y());
}

/*!
 * \fn  void Editeur::construire1mur(QGraphicsScene * scene,
                    const int& nbPorte,
                    const QPointF & depart,
                    const QPointF & arrivee,
                    const QPointF & inter_1_1,
                    const QPointF & inter_1_2,
                    const QPointF & inter_2_1,
                    const QPointF & inter_2_2)
 *
 * \brief Construit un mur en tenant compte des portes.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param scene ( Entrée / Sortie ) La scène.
 * \param nbPorte ( Entrée ) Le nombre de portes présentes dans le mur.
 * \param depart ( Entrée ) Le point topleft du mur.
 * \param arrivee ( Entrée ) Le point bottomright du mur.
 * \param inter_1_1 ( Entrée ) Le point topleft de la porte la plus en haut ou à gauche.
 * \param inter_1_2 ( Entrée ) Le point bottomright de la porte la plus en haut ou à gauche.
 * \param inter_2_1 ( Entrée ) Le point topleft de la porte la plus en bas ou à droite.
 * \param inter_2_2 ( Entrée ) Le point bottomright de la porte la plus en bas ou à droite.
 *
 */
void Editeur::construire1mur(QGraphicsScene * scene,
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

/*!
 * \fn  void Editeur::creer_murs(QGraphicsScene * scene, const QPointF& TL_1, const QPointF& TL_2)
 *
 * \brief Créer les 4 murs de la pièce.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param scene ( Entrée / Sortie ) La scène.
 * \param TL_1 ( Entrée ) Le point topleft de la première porte.
 * \param TL_2 ( Entrée ) Le point topleft de la deuxième porte.
 *
 */
void Editeur::creer_murs(QGraphicsScene * scene, const QPointF& TL_1, const QPointF& TL_2)
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


/***************************************METHODES PUBLIQUES*********************************************************/

/*!
 * \fn  Editeur::Editeur(const QGraphicsScene * scene)
 *
 * \brief Constructeur avec paramètre.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param scene ( Entrée / Sortie ) La scène.
 *
 */
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


/*!
 * \fn  void Editeur::cartographier()
 *
 * \brief Créer la map d'élévation pour la fuite des persnnages normaux.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
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

/*!
 * \fn  void Editeur::creer_limites(QGraphicsScene * scene)
 *
 * \brief Créer les portes et les murs de la salle.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param scene ( Entrée / Sortie ) La scène.
 *
 */
void Editeur::creer_limites(QGraphicsScene * scene)
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

/*!
 * \fn  void Editeur::installer_personnage(QGraphicsScene * scene)
 *
 * \brief Installe les personnages dans la pièce.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param scene ( Entrée / Sortie ) La scène.
 *
 */
void Editeur::installer_personnage(QGraphicsScene * scene)
{
    int nbNormaux = 30; //à changer !

    int moduloX = width_ - 40;
    int moduloY = height_ - 40;

    std::vector<Personnage*> listPerso;

    //Placement de l'assassin
    Assassin* assassin = new Assassin(0);
    assassin->setPos(change_repere(QPoint((qreal)(qrand()%moduloX + 20 ), (qreal)(qrand()%moduloY + 20 ))));
    scene->addItem(assassin);

    listPerso.push_back(assassin);

    //Placement de la cible
    Cible* cible = new Cible(0);
    bool enoughFar = false;
    do{
        cible->setPos(change_repere(QPoint((qreal)(qrand()%moduloX + 20),(qreal)( qrand()%moduloY + 20))));
        QPointF posAssassin = assassin->pos();
        QPointF posCible = cible->pos();

        enoughFar = !cible->collidesWithItem(assassin)
                && QLineF(posAssassin, posCible).length() > 130.0f;


    } while( !enoughFar );
    scene->addItem(cible);
    listPerso.push_back(cible);

    //Placement des surveillants

    //Placement des normaux
    for(int i = 0; i < nbNormaux; ++i)
    {
        int nbIteration = 0 ;
        Normal* normal = new Normal(0);
        bool collide = true;

        do
        {
            normal->setPos(change_repere(QPoint((qreal)(qrand()%moduloX + 20 ),(qreal) (qrand()%moduloY + 20 ))));

            foreach(Personnage* p, listPerso)
            {
                if( (collide = normal->collidesWithItem(p) ))
                    break;
            }

            ++nbIteration;
        } while( collide && nbIteration < 100);

        if( !collide)
        {
            scene->addItem(normal);
            listPerso.push_back(normal);
        }
    }
}

/*!
 * \fn  QTextStream& operator<<( QTextStream& o, const QGraphicsItem * pQGI)
 *
 * \brief Opérateur de flux.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param o ( Entrée / Sortie ) Flux.
 * \param pQGI ( Entrée / Sortie ) L'item à afficher.
 *
 * \return Référence sur le flux.
 */
QTextStream& operator<<( QTextStream& o, const QGraphicsItem * pQGI)
{
     // Récupération du type d'élément
     QString s = typeid(*pQGI).name();
     s = s.toUpper();
     s = s.remove(0, 6);

     // Cas particulier pour les murs dont on inscrit les coordonnées topleft et bottomright de la boîte englobante
     if( s == "MUR" )
     {
         o << s << "\nTL " << pQGI->boundingRect().topLeft().x() << " " << pQGI->boundingRect().topLeft().y()
          <<"\nBR " <<  pQGI->boundingRect().bottomRight().x() << " " <<  pQGI->boundingRect().bottomRight().y() << "\n\n";
     }
     else // Tous les autres items n'ont besoin que de leur position
        o << s << "\nPOS "<< pQGI->pos().x() << " " << pQGI->pos().y() << "\n\n";

    return o;
}
