/*!
 * \file  "Editeur.hpp"
 *
 * \brief Fichier contenant la déclaration des méthodes de la classe réprésentant l'éditeur de la scène.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */

#ifndef EDITEUR_HPP
#define EDITEUR_HPP

#include "Include.hpp"
#include "Mur.hpp"
#include "Porte.hpp"
#include "Assassin.hpp"
#include "Cible.hpp"
#include "Normal.hpp"

/*!
 * \enum COULEUR
 *
 * \brief Indique si le pixel a été traité ou non.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
enum COULEUR
{
    BLANC,
    GRIS,
    NOIR
};

/*!
 * \struct Pixel
 *
 * \brief Structure indiquant le niveau d'un pixel de la scène
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
typedef struct Pixel
{
    int niveau;
    COULEUR coul;
}Pixel;

/*!
 * \class Editeur
 *
 * \brief Editeur de map de la scène
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
class Editeur
{
    /***************************************METHODES PUBLIQUES*********************************************************/
public :

    /*! \brief Constructeur */
    Editeur(const QGraphicsScene *);

    /*! \brief Cartographie de la map */
    void cartographier();

    /*! \brief Création des contours de la scène avec les portes */
    void creer_limites(QGraphicsScene *);

    /*! \brief Mise en place des différents personnages */
    void installer_personnage(QGraphicsScene *);

    /*! \brief Pour stocker dans un fichier */
    friend QTextStream& operator<<( QTextStream& o, const QGraphicsItem * pQGI);

private :

    /***************************************METHODES PRIVEES*********************************************************/

    /*! \brief Retourne vrai si le point n'a pas été traité dans la cartographie */
    bool verifier_traitement(const QList<QGraphicsItem*>&, const QPointF &);

    /*! \brief Sauvegarde des items de la scène et la grille d'élévation dans un fichier */
    void sauver_grille();

    /*! \brief Inverse les coordonnées d'un point */
    QPointF reverseCoord(const QPointF &);

    /*! \brief Ajout de la coordonnée y des points dans la file de priorité si la coordonnées x correspond à une certaine valeur */
    void ajouterTL(std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > &, const QPointF&, const QPointF&, const qreal&);

    /*! \brief Construit un mur dans la scène en tenant compte des portes*/
    void construire1mur(QGraphicsScene *, const int&,
                        const QPointF&,
                        const QPointF&,
                        const QPointF&,
                        const QPointF&,
                        const QPointF&,
                        const QPointF&);

    /*! \brief Création d'un mur entre deux points */
    void creer_murs(QGraphicsScene *, const QPointF&, const QPointF&);


    /***************************************DONNEES MEMBRES*********************************************************/
    /*! \brief Scène */
    const QGraphicsScene * scene_;

    /*! \brief Grille d'élévation pour la fuite */
    std::vector<Pixel> grille_;

    /*! \brief Largeur de la scène */
    int width_;

    /*! \brief Hauteur de la scène */
    int height_;

    /*! \brief Largeur de la scène murs compris */
    int elemSize_;


};

#endif // EDITEUR_HPP
