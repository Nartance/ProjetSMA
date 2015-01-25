#ifndef MUR_HPP
#define MUR_HPP

#include "Include.hpp"

class Mur : public QGraphicsItem
{
    public :
        Mur(const int &);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

    protected:
        void advance(int);

    private :
        int mur_;

};

#endif // MUR_HPP
