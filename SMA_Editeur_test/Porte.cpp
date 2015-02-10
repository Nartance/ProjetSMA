/*!
 * \file  "Porte.cpp"
 *
 * \brief Fichier contenant la définition des méthodes de la classe réprésentant les portes.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */

#include "Porte.hpp"

/*!
 * \fn  Porte::Porte(const Porte &)
 *
 * \brief Constructeur par copie.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
Porte::Porte(const Porte &)
{

}


/*!
 * \fn  Porte::Porte()
 *
 * \brief Constructeur par défaut choisissant un mur de manière randomisée (de 0 à 3 pour chaque pan de mur).
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
Porte::Porte() : mur_(qrand() % 4)
{

}

/*!
 * \fn  void Porte::positionnerPorte()
 *
 * \brief Positionne la porte sur le mur associé de manière randomisée.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
void Porte::positionnerPorte()
{
    qreal x_mur_gauche = 49;
    qreal x_mur_droite = scene()->width() - 50;
    qreal y_mur_haut = 49;
    qreal y_mur_bas = scene()->height() - 50;

    int taille_mur = 30;
    int moduloX = x_mur_droite - taille_mur - x_mur_gauche ;
    int moduloY = y_mur_bas - taille_mur - y_mur_haut;

    qreal xHaut, yDroite, xBas, yGauche ;

    switch(mur_)
    {
        case 0: // mur du haut
            xHaut = (qreal)(qrand() % moduloX) + x_mur_gauche;
            boite_.setRect(xHaut, y_mur_haut, taille_mur, 1);
            break;

        case 1: // mur de droite
            yDroite = (qreal)(qrand() % moduloY) + y_mur_haut ;
            boite_.setRect(x_mur_droite, yDroite, 1, taille_mur);
            break;

        case 2: // mur du bas
            xBas = (qreal)(qrand() % moduloX) + x_mur_gauche ;
            boite_.setRect(xBas, y_mur_bas, taille_mur, 1);
            break;

        case 3: // mur de gauche
            yGauche = (qreal)(qrand() % moduloY )+ y_mur_haut ;
            boite_.setRect(x_mur_gauche, yGauche, 1, taille_mur);
            break;
    }
}

/*!
 * \fn  QRectF Porte::boudingRect() const
 *
 * \brief Détermine la forme englobante de l'objet.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \return Le rectangle englobant de l'objet.
 */
QRectF Porte::boundingRect() const
{
    return boite_;
}

/*!
 * \fn  QPainterPath Porte::shape() const
 *
 * \brief Détaille la forme englobante de l'objet.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \return Le painterpath associé.
 */
QPainterPath Porte::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

/*!
 * \fn  void Porte::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
 *
 * \brief Dessine l'objet.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param painter ( Entrée / Sortie ) Le painter.
 */
void Porte::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Couleur du trace
    painter->setPen(QPen(QColor(255,0,255)));
    painter->setBrush(QBrush(QColor(255,0,255)));
    painter->drawRect(boundingRect());

}

/*!
 * \fn void Porte::advance(int phase)
 *
 * \brief Fait déplacer l'objet.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param phase ( Entrée ) Le pas d'avancement.
 */
void Porte::advance(int phase)
{
    if(!phase)
        return;
}
