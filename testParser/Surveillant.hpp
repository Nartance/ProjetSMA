#ifndef SURVEILLANT_HPP
#define SURVEILLANT_HPP

#include "Personnage.hpp"

class Surveillant : public Personnage
{
    public :
        Surveillant(const int &, bool affichage = false);
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

    protected:
        void action(const QList<QGraphicsItem *> &);
        void move();

    private :
        bool affichage_;
};

#endif // SURVEILLANT_HPP
