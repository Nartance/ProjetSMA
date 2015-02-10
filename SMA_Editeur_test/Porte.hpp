/*!
 * \file  "Porte.hpp"
 *
 * \brief Fichier contenant la déclaration des méthodes de la classe réprésentant les portes.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */

#ifndef PORTE_HPP
#define PORTE_HPP

#include "Include.hpp"

/*!
 * \class Porte
 *
 * \brief Porte de sortie de la salle.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
class Porte : public QGraphicsItem
{
    public :
        /*! \brief Constructeur */
        Porte();

        /*! \brief Constructeur par copie */
        Porte(const Porte &);

        /*! \brief Positionner la porte sur un mur */
        void positionnerPorte();

        /*! \brief Boîte englobante */
        QRectF boundingRect() const;

        /*! \brief Forme détaillée de l'objet */
        QPainterPath shape() const;

        /*! \brief Dessin de l'objet */
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

        /*! \brief Affiche le type d'objet */
        void type();

        /*! \brief Accesseur du mur associé à la porte */
        int getMur() {return mur_;}

    protected:

        /*! \brief Fonction héritée permettant de déplacer l'objet (inutilisée ici) */
        void advance(int);

    private :
        /*! \brief Mur associé à la porte */
        int mur_;

        /*! \brief Boîte englobante */
        QRect boite_;

};

#endif // PORTE_HPP

