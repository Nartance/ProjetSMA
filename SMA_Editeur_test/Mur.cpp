#include "Mur.hpp"

Mur::Mur(const QPointF & TL, const QPointF & BR) : TL_(TL), BR_(BR)
{

}

// Forme englobante
QRectF Mur::boundingRect() const
{
    QRectF boite;

    boite.setTopLeft(TL_);
    boite.setBottomRight(BR_);

    return boite;
}

// Forme détaillé
QPainterPath Mur::shape() const
{
    QPainterPath path;

    path.addRect(boundingRect());

    return path;
}

void Mur::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Couleur du trace
    painter->setPen(QPen(QColor(0,0,0)));
    painter->setBrush(QBrush(QColor(0,0,0)));
    painter->drawRect(boundingRect());
}

void Mur::advance(int phase)
{
    if(!phase)
        return;
}
