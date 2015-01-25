#ifndef NORMAL_HPP
#define NORMAL_HPP

#include "General.hpp"
#include "Personnage.hpp"

class Normal : public Personnage
{
    public :
        Normal(const int &, bool affichage = false);
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
        void type();

    protected:
        void action(const QList<QGraphicsItem *> &);
        void move();

    private :
        bool affichage_;
        bool panique_;

        // Gestion du choc
        qreal temps_;
        qreal angle_arret_;

        QTime * pause_;
};

#endif // NORMAL_HPP
