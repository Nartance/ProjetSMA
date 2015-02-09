#include "Cible.hpp"

Cible::Cible(const int & angle = 0, bool affichage) : Personnage(angle), affichage_(affichage)
{
    mort_ = false;
}

void Cible::paint(QPainter * painter, const QStyleOptionGraphicsItem * qsogt, QWidget * qw)
{
    if(!mort_)
        painter->setBrush(QBrush(QColor(0,0,220)));
    else
    {
        painter->setPen(QPen(QColor(136,6,6)));
        painter->setBrush(QBrush(QColor(136,6,6)));
        painter->drawEllipse(-12,-10,18,20);
        painter->drawEllipse(2,2,10,10);

        painter->setBrush(QBrush(QColor(110,190,220)));
    }

    Personnage::paint(painter, qsogt, qw);
}

void Cible::mort()
{
    mort_ = true;
}

void Cible::type()
{
    std::cout << "Cible" << std::endl;
}

void Cible::action(const QList<QGraphicsItem *> & liste_item)
{
    //Mouvement circulaire de test - position initiale : (350,200) angle = 90
    /*++angle_;
    vitesse_ = 2.5;*/

    Personnage::action(liste_item);
}

void Cible::move()
{
    if(!mort_)
    {
        setRotation(angle_);
        setPos(mapToParent(vitesse_deplacement_,0));
    }
}

