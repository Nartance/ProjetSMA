#ifndef MUR_HPP
#define MUR_HPP

#include "main.hpp"

class Mur : public QGraphicsItem
{
    public :
        Mur(const int &);
        Mur(const QPointF &, const QPointF &);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

    protected:
        void advance(int);

    private :
        int mur_;
        QPointF TL_;
        QPointF BR_;

};

#endif // MUR_HPP
