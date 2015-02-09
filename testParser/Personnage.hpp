#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include "Include.hpp"

class Personnage : public QGraphicsItem
{
    public:
        Personnage(const int & angle = 0);

        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        virtual void type() = 0;

        void setMatrice(const matInt &);

    protected:
        void advance(int);
        virtual void action(const QList<QGraphicsItem *> &);
        virtual void move();

        QPointF deplacement_angle() const;
        QPointF regard() const;

        qreal angle_;

        matInt grille_;

        qreal vitesse_;
        qreal vitesse_deplacement_;

        qreal angle_modifie_;
        qreal compteur_;
        qreal limite_;
    private:

};

#endif // PERSONNAGE_HPP
