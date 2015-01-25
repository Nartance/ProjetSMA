#include "Porte.hpp"

Porte::Porte(const Porte &)
{

}

Porte::Porte() : mur_(qrand() % 4)
{

}

void Porte::positionnerPorte()
{
    qreal x_mur_gauche = 49;
    qreal x_mur_droite = scene()->width() - 50;
    qreal y_mur_haut = 49;
    qreal y_mur_bas = scene()->height() - 50;

    int taille_mur = 30;
    int moduloX = x_mur_droite - taille_mur - x_mur_gauche ;
    int moduloY = y_mur_bas - taille_mur - y_mur_haut;

    qreal xHaut, yDroite, xBas, yGauche ;

    switch(mur_)
    {
        case 0: // mur du haut
            xHaut = (qreal)(qrand() % moduloX) + x_mur_gauche;
            boite_.setRect(xHaut, y_mur_haut, taille_mur, 1);
            break;

        case 1: // mur de droite
            yDroite = (qreal)(qrand() % moduloY) + y_mur_haut ;
            boite_.setRect(x_mur_droite, yDroite, 1, taille_mur);
            break;

        case 2: // mur du bas
            xBas = (qreal)(qrand() % moduloX) + x_mur_gauche ;
            boite_.setRect(xBas, y_mur_bas, taille_mur, 1);
            break;

        case 3: // mur de gauche
            yGauche = (qreal)(qrand() % moduloY )+ y_mur_haut ;
            boite_.setRect(x_mur_gauche, yGauche, 1, taille_mur);
            break;
    }
}
// Forme englobante
QRectF Porte::boundingRect() const
{
    return boite_;
}

// Forme détaillé
QPainterPath Porte::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Porte::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Couleur du trace
    painter->setPen(QPen(QColor(255,0,255)));
    painter->setBrush(QBrush(QColor(255,0,255)));
    painter->drawRect(boundingRect());

}

void Porte::advance(int phase)
{
    if(!phase)
        return;
}
