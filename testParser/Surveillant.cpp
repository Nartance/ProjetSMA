#include "Surveillant.hpp"

Surveillant::Surveillant(const int & angle = 0, bool affichage) : Personnage(angle), affichage_(affichage)
{

}

void Surveillant::paint(QPainter * painter, const QStyleOptionGraphicsItem * qsogt, QWidget * qw)
{
    painter->setBrush(QBrush(QColor(0,220,0)));
    Personnage::paint(painter, qsogt, qw);
}

void Surveillant::type()
{
    std::cout << "Surveillant" << std::endl;
}

void Surveillant::action(const QList<QGraphicsItem *> & liste_item)
{

}

void Surveillant::move()
{
    /*setRotation(angle_);
    setPos(mapToParent(vitesse_deplacement_,0));*/
}


