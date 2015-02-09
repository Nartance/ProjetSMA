#ifndef MUR_HPP
#define MUR_HPP

#include "Include.hpp"

class Mur : public QGraphicsItem
{
    public :
        Mur(const QPointF &, const QPointF &);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

    protected:
        void advance(int);

    private :
        QPointF TL_;
        QPointF BR_;

};

#endif // MUR_HPP
