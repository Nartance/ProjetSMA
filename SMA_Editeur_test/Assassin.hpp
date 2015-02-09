#ifndef ASSASSIN_HPP
#define ASSASSIN_HPP

#include "General.hpp"
#include "Personnage.hpp"

class Assassin : public Personnage
{
    public :
        Assassin(const int &, bool affichage = false);
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

        QPointF origine_tir_;

    protected:
        void action(const QList<QGraphicsItem *> &);
        void move();

    private :
        bool affichage_;

        QTime * visee_;
};

#endif // ASSASSIN_HPP
