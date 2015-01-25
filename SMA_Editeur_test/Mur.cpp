#include "Mur.hpp"

Mur::Mur(const int & mur) : mur_(mur)
{

}

Mur::Mur(const QPointF & TL, const QPointF & BR) : mur_(-1), TL_(TL), BR_(BR)
{

}

// Forme englobante
QRectF Mur::boundingRect() const
{
    QRectF boite;

    switch(mur_)
    {
        case -1 :
            boite.setTopLeft(TL_);
            boite.setBottomRight(BR_);
            break;

        case 0 :
            boite.setRect(scene()->width() - 50, 50, 1, scene()->height() - 100);
            break;

        case 1 :
            boite.setRect(50, scene()->height() - 50, scene()->width() - 100, 1);
            break;

        case 2 :
            boite.setRect(50, 50, 1, scene()->height() - 100);
            break;

        case 3 :
            boite.setRect(50, 50, scene()->width() - 100, 1);
            break;
    }

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
