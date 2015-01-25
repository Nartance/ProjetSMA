#ifndef PORTE_HPP
#define PORTE_HPP

#include "main.hpp"

class Porte : public QGraphicsItem
{
    public :
        Porte();
        Porte(const Porte &);

        void positionnerPorte();

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

        int getMur() {return mur_;}

    protected:
        void advance(int);

    private :
        int mur_;
        QRect boite_;

};

#endif // PORTE_HPP

