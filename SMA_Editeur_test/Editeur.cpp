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

    // Recherche de l'appartenance du point dans un des items
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
    // Fichier de sortie
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

    //Enregistrement des données de la map d'élévation
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
   // Selon le nombre de portes que contient le mur, on sépare ledit mur en 0, 1 ou 2
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
    // Frontières de la scène
    qreal x_mur_gauche = 49;
    qreal x_mur_droite = scene->width() - 50;
    qreal y_mur_haut = 49;
    qreal y_mur_bas = scene->height() - 50;

    qreal taille_porte = 30;

    // Point topleft du mur
    QPointF depart;

    // Point bottomright du mur
    QPointF arrivee;

    // Point topleft de la porte 1
    QPointF inter_1_1;

    // Point bottomright de la porte 1
    QPointF inter_1_2;

    // Point topleft de la porte 2
    QPointF inter_2_1;

    // Point bottomright de la porte 2
    QPointF inter_2_2;

    // Nombre de porte sur un mur
    int nbPorte;

    // Parcours de chaque mur de la pièce
    for( int i = 0; i < 4; ++i )
    {
        // File de priorité sur les coordonnées croissantes des portes
        std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > coordonnees;

        switch(i)
        {
            case 0 : // Mur de droite

                // Stockage des points limites du mur
                depart = QPointF(x_mur_droite, 50);
                arrivee = QPointF(x_mur_droite + 1, y_mur_bas);

                // On ajoute les portes qui sont sur ce mur (s'il y en a)
                ajouterTL(coordonnees, TL_1, TL_2, x_mur_droite);
                nbPorte = coordonnees.size();

                // S'il y a au moins une porte, il fzut scindé le mur
                if(nbPorte > 0)
                {
                    // Une seule porte : on le sépare en deux
                    inter_1_1 = QPointF(x_mur_droite + 1, coordonnees.top());
                    inter_1_2 = QPointF(x_mur_droite, coordonnees.top() + taille_porte);

                    // Deux portes : on le sépare en trois
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

        // Construction du mur en fonction du nombre de portes qu'il possède
        construire1mur(scene, nbPorte, depart, arrivee, inter_1_1, inter_1_2, inter_2_1, inter_2_2);

    }
}

/*!
 * \fn  bool Editeur::test_ajout_item(QGraphicsItem *item, const int & moduloX, const int & moduloY, const int & errorX, , const int & errorY)
 *
 * \brief Essaie de placer un item dans la scène sans collision.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param item ( Entrée ) L'item à tester.
 * \param moduloX ( Entrée ) Le modulo en abscisse.
 * \param moduloY ( Entrée ) Le modulo en ordonnée.
 * \param errorX ( Entrée ) Variation à ajouter en x.
 * \param errorY ( Entrée ) Variation à ajouter en y.
 *
 * \return True si l'objet ne collisionne personne.
 */
bool Editeur::test_ajout_item(QGraphicsItem * item, const int & moduloX, const int & moduloY, const int & errorX , const int & errorY)
{
    // Pour éviter de tourner en rond
    int nbIteration = 0 ;

    // Indicatif de collision
    bool collide = false;

    do
    {
        // Tentative de positionnement
        item->setPos(change_repere(QPoint((qreal)(qrand()%moduloX + errorX ),(qreal) (qrand()%moduloY + errorY ))));

        // Vérifier la collision avec les autres items
        foreach(QGraphicsItem* pQGI, listItem_)
        {
            if( (collide = item->collidesWithItem(pQGI) ))
                break;
        }

        ++nbIteration;

    } while(collide && nbIteration < 100);

    return !collide;
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
    // Dimension de la scène
    width_ = (int) scene->width(); width_ -= 100;
    height_ = (int) scene->height(); height_ -= 100;

    // Dimension d'une largeur en comprenant les murs
    elemSize_ = width_ + 2 ;

    // Initialisation de la map d'élévation
    grille_ = std::vector<Pixel>( elemSize_ * (height_ + 2));

    for( std::vector<Pixel>::iterator it = grille_.begin() ; it != grille_.end() ; ++it)
    {
        // Niveau -1 (correspond aux murs)
        it->niveau = -1;

        // Pixel non visité
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
    // Liste des pixels de la scène
    std::vector<QPointF> liste_initiale;

    // Liste des pixels à traiter
    std::vector<QPointF> a_traiter;

    // On récupère les items de la scène
    QList<QGraphicsItem *> liste_item = scene_->items();

    // On enlève la salle
    liste_item.pop_front();

    // Cartographie des portes (niveau 0)
    for( int i = 0 ; i < 2 ; ++i )
    {
        // Récupération des points limites de la porte
        QPointF TL = liste_item[i]->boundingRect().topLeft();
        QPointF BR = liste_item[i]->boundingRect().bottomRight();

        // Porte verticale
        if(BR.x() - TL.x() == 1)
        {
            for( qreal var = TL.y(); var < BR.y(); ++var )
            {
                // On rajoute chaque point de la porte dans la liste initiale
                liste_initiale.push_back(QPointF(TL.x(), var));
            }
        }
        else // Porte horizontale
        {
            for( qreal var = TL.x(); var < BR.x(); ++var )
            {
                // On rajoute chaque point de la porte dans la liste initiale
                liste_initiale.push_back(QPointF(var, TL.y()));
            }
        }
    }

    liste_item.pop_front(); // on enlève la porte 1
    liste_item.pop_front(); // on enlève la porte 2

    int niveau = 0;

    // Parcours : élévation par vague à partir des portes
    while(!liste_initiale.empty())
    {
        // On traite les points de la liste en ajoutant le niveau courant
        for(std::vector<QPointF>::iterator it = liste_initiale.begin(); it != liste_initiale.end(); ++it)
        {
            int indice = (int) it->x() - 49 + elemSize_ * ( (int) it->y() - 49 ) ;
            grille_[ indice ].niveau = niveau;
            grille_[ indice ].coul = NOIR;
        }

        // On prend tous les pixels voisins des pixels de la liste afin de les traiter dans la prochaine vague
        for(std::vector<QPointF>::iterator it = liste_initiale.begin(); it != liste_initiale.end(); ++it)
        {
            int itX = (int) it->x() - 49 ;
            int itY = (int) it->y() - 49 ;

            // Les pixels autour du pixel courant
            int indiceHaut = itX + elemSize_ * ( itY - 1 );
            int indiceBas = itX + elemSize_ * ( itY + 1 ) ;
            int indiceGauche = (itX - 1) + elemSize_ * itY ;
            int indiceDroite = (itX + 1) + elemSize_ * itY ;

            QPointF ptAjout;

            // On regarde chaque pixel autour du pixel courant. S'il n'est pas traité, on l'ajoute à la liste

            // Pixel du haut
            if( itY - 1 > 0 && grille_[ indiceHaut ].coul == BLANC )
            {
                // Point à ajouter
                ptAjout = QPointF(it->x(), it->y() - 1);

                // Si le point n'intersecte aucun objet dans la scène
                if( verifier_traitement( liste_item, ptAjout) )
                {
                    // On ajoute la point dans la liste des pixels à traiter au prochain tour
                    a_traiter.push_back(ptAjout);

                    // On le marque comme étant visité
                    grille_[ indiceHaut ].coul = GRIS;
                }
            }

            // Pixel du bas
            if( itY + 1 < height_ + 2 && grille_[ indiceBas ].coul == BLANC )
            {
                ptAjout = QPointF(it->x(), it->y() + 1);

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceBas ].coul = GRIS;
                }
            }

            // Pixel de droite
            if( itX + 1 < elemSize_ && grille_[ indiceDroite ].coul == BLANC )
            {
                ptAjout = QPointF(it->x() + 1, it->y());

                if( verifier_traitement( liste_item, ptAjout) )
                {
                    a_traiter.push_back(ptAjout);
                    grille_[ indiceDroite ].coul = GRIS;
                }
            }

            // Pixel de gauche
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

        // On efface la liste courante
        liste_initiale.clear();

        // On met à jour avec les nouveaux pixels à traiter
        liste_initiale = a_traiter;

        // Nettoyage de a_traiter
        a_traiter.clear();

        // On passe au niveau suivant
        ++niveau;
    }

    // Dès que la grille est complète, on enregistre le tout dans un fichier
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
    // Initialisation de la seed
    srand(time(0));

    // Première porte
    Porte* porte_1 = new Porte();

    // La deuxième porte ne doit pas empiéter sur la seconde
    Porte* porte_2 = 0;

    // Positionnement et ajout de la porte
    scene->addItem(porte_1);
    porte_1->positionnerPorte();

    // Stockage du point topleft de la porte
    qreal p1x = porte_1->boundingRect().topLeft().x();
    qreal p1y = porte_1->boundingRect().topLeft().y();

    bool sempiete;

    // Recherche d'une place correcte pour la deuxième porte (nécessaire si els deux portes sont
    // sur le même mûr
    do{
        sempiete = false;

        // Création, positionnement et ajout de la porte
        porte_2 = new Porte();
        scene->addItem(porte_2);
        porte_2->positionnerPorte();

        // Récupération du point topleft de la porte 2
        qreal p2x = porte_2->boundingRect().topLeft().x();
        qreal p2y = porte_2->boundingRect().topLeft().y();

        // Le choix de l'espace entre deux porte sur un même mûr a été choisi à 40 pixels de différence
        if((p1y == p2y && abs(p1x - p2x) < 40)
               || (p1x == p2x && abs(p1y - p2x) < 40 ))
        {
            // Si les portes s'empiètent, on supprime la porte et on réessaie
            delete porte_2;
            sempiete = true;
        }

    } while ( sempiete );

    // Une fois les portes placées, on construit les quatre murs de la scène
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
    // Nombre de normaux
    int nbNormaux = 30;

    // Nombre de surveillants
    int nbSurveillants = 3;

    // Modulo à appliquer sur la positionnement des personnages
    int moduloX = width_ - 40;
    int moduloY = height_ - 40;
    int error = 20 ;

    // Limite de bande pour le placement initial des suveillants
    std::vector<QVector4D> bandeSurveillant;

    // Limite bande du haut
    QVector4D bandeHaut (moduloX, (qreal)( 0.25f * height_ ), error, error);
    bandeSurveillant.push_back(bandeHaut);

    // Limite bande du bas
    QVector4D bandeBas (moduloX, (qreal)(0.25f * height_), error , (qreal)(0.75f * height_) - error);
    bandeSurveillant.push_back(bandeBas);

    // Limite bande de droite
    QVector4D bandeDroite ((qreal)( 0.25f  * width_ ), moduloY, (qreal)( 0.75f  * width_ )- error, error);
    bandeSurveillant.push_back(bandeDroite);

    // Limite bande de gauche
    QVector4D bandeGauche ((qreal)( 0.25f * width_ ), moduloY, error, error);
    bandeSurveillant.push_back(bandeGauche);

    //Placement des surveillants
    for(int i = 0 ; i < nbSurveillants; ++i)
    {
        Surveillant* surveillant = new Surveillant(0);

        int index = i % 4 ;

        if( test_ajout_item(surveillant, bandeSurveillant[index].x(),
                                         bandeSurveillant[index].y(),
                                         bandeSurveillant[index].z(),
                                         bandeSurveillant[index].w()))
        {
            scene->addItem(surveillant);
            listItem_.push_back(surveillant);
        }
    }

    //Placement de l'assassin
    Assassin* assassin = new Assassin(0);

    // Parce qu'il nous faut un assassin !
    while(!test_ajout_item(assassin, moduloX, moduloY, error, error));

    scene->addItem(assassin);
    listItem_.push_back(assassin);

    //Placement de la cible
    Cible* cible = new Cible(0);

    // On veut la cible suffisamment éloignée de l'assasssin
    bool enoughFar = false;

    // Tant qu'elle n'est pas assez loin, on réessaie
    while( !enoughFar && !test_ajout_item(cible, moduloX, moduloY, error, error) )
    {
        QPointF posAssassin = assassin->pos();
        QPointF posCible = cible->pos();

        // La distance minimale entre l'assassin et la cible a été choisie au 2/3 de la plus grande dimension
        enoughFar = !cible->collidesWithItem(assassin)
                && QLineF(posAssassin, posCible).length() > (qreal)std::max(width_, height_) / 1.5f;

    }

    // On ajoute la cible
    scene->addItem(cible);
    listItem_.push_back(cible);

    //Placement des normaux
    for(int i = 0; i < nbNormaux; ++i)
    {
        // Création du normal
        Normal* normal = new Normal(0);
        if( test_ajout_item(normal, moduloX, moduloY, error, error) )
        {
            scene->addItem(normal);
            listItem_.push_back(normal);
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
