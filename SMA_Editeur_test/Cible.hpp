#ifndef CIBLE_HPP
#define CIBLE_HPP

#include "Personnage.hpp"

class Cible : public Personnage
{
    public :
        Cible(const int &, bool affichage = false);
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void mort();
        void type();

    protected:
        void action(const QList<QGraphicsItem *> &);
        void move();

    private :
        bool affichage_;
        bool mort_;
};

#endif // CIBLE_HPP

