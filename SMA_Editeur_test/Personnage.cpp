#include "Personnage.hpp"

QPointF direction[3] = { QPointF(5.3,-5.3), QPointF(0,0), QPointF(5.3,5.3) };

Personnage::Personnage(const int & angleT) : angle_(angleT), vitesse_(1), compteur_(-1), limite_(-1)
{
    vitesse_deplacement_ = vitesse_;
}

// Forme englobante
QRectF Personnage::boundingRect() const
{
    return QRectF(-7.5, -7.5, 15, 15);
}

// Forme détaillé - Au final je suis pas sur que le programme l'utilise
QPainterPath Personnage::shape() const
{
    QPainterPath path;
    path.addEllipse(-7.5,-7.5,15,15);
    return path;
}

void Personnage::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Couleur du trace
    painter->setPen(QPen(QColor(0,0,0)));

    // Corps
    painter->drawEllipse(-7.5,-7.5,15,15);

    // Regard
    painter->drawPolyline(direction, 3);
}

void Personnage::setMatrice(const matInt & grille)
{
    grille_ = grille;
}

void Personnage::advance(int phase)
{
    if(!phase)
        return;

    QList<QGraphicsItem *> liste_item = scene()->items();
    liste_item.pop_front();

    bool collision = false;
    bool detection = false;
    qreal angle_attaque;
    qreal distance = 40;
    qreal vitesse = vitesse_;

    foreach (QGraphicsItem * item, liste_item)
    {
        if(item == this)
            continue;

        QRectF boite_collision = QRectF(item->pos() + item->boundingRect().topLeft(), item->pos() + item->boundingRect().bottomRight());
        QRectF boite_englobante = QRectF(this->pos() - QPointF(10,10), this->pos() + QPointF(10,10));

        // Détecte la collision
        if(boite_collision.intersects(boite_englobante))
        {
            collision = true;
            break;
        }
        else
        {
            QRectF boite_projete = boite_englobante;
            qreal i = 0;

            while(i < distance)
            {
                ++i;
                boite_projete.moveTopLeft(boite_projete.topLeft() + deplacement_angle());

                if(boite_collision.intersects(boite_projete))
                {
                    QRectF intersection = boite_collision.intersected(boite_projete);
                    std::vector<QLineF> lignes;

                    lignes.push_back(QLineF(this->pos(), intersection.topLeft())); // topLeft
                    lignes.push_back(QLineF(this->pos(), QPointF((intersection.topLeft().x() + intersection.topRight().x()) / 2,intersection.topLeft().y()))); // middleTop
                    lignes.push_back(QLineF(this->pos(), intersection.topRight())); // topRight
                    lignes.push_back(QLineF(this->pos(), QPointF(intersection.topRight().x(), (intersection.topRight().y() + intersection.bottomRight().y()) / 2))); // middleRight
                    lignes.push_back(QLineF(this->pos(), intersection.bottomRight())); // bottomRight
                    lignes.push_back(QLineF(this->pos(), QPointF((intersection.bottomLeft().x() + intersection.bottomRight().x()) / 2,intersection.bottomLeft().y()))); // middleBottom
                    lignes.push_back(QLineF(this->pos(), intersection.bottomLeft())); // bottomLeft
                    lignes.push_back(QLineF(this->pos(), QPointF(intersection.topLeft().x(), (intersection.topLeft().y() + intersection.bottomLeft().y()) / 2))); // middleLeft

                    sort(lignes.begin(), lignes.end(), minimum_distance_QLineF());
                    angle_attaque = lignes[0].angleTo(QLineF(this->pos(), regard()));

                    detection = true;
                }
            }
        }
    }

    if(collision == true)
    {
        angle_ = normalise_angle(angle_ + 180);
        /*
        if(limite_ == -1)
        {
            vitesse_ = 0;
            angle_modifie_ = 10;
            limite_ = 18;
        }
        else
        {
            if(compteur_ < limite_)
            {
                angle_ += angle_modifie_;
                ++compteur_;
            }
            else
            {
                vitesse_ = 1;
                compteur_ = -1;
                limite_ = -1;
            }
        }*/
    }
    else if(detection == true)
    {
        vitesse = (vitesse_ / 50) * distance;

        if(normalise_angle(angle_attaque) > 180)
            angle_ += (50/distance) + distance/7;
        else
            angle_ -= (50/distance) + distance/7;
    }
    else
    {
        action(liste_item);
    }

    move();
}

void Personnage::action(const QList<QGraphicsItem *> &)
{
    if(limite_ == -1)
    {
        angle_modifie_ = qrand() % 10 - 5;
        limite_ = qrand() % 50;
    }
    else
    {
        if(compteur_ < limite_)
        {
            angle_ += angle_modifie_;
            ++compteur_;
        }
        else
        {
            compteur_ = -1;
            limite_ = -1;
        }
    }
}

void Personnage::move()
{
    setRotation(angle_);
    setPos(mapToParent(vitesse_deplacement_,0));
}

QPointF Personnage::deplacement_angle() const
{
    QPointF pas = QPointF(0,0);

    pas.setX(qCos((qreal) angle_ * 3.1415926535 / 180));
    pas.setY(qSin((qreal) angle_ * 3.1415926535 / 180));

    return pas;
}

QPointF Personnage::regard() const
{
    qreal x = this->pos().x() + 50 * qCos((qreal) angle_ * 3.1415926535 / 180);
    qreal y = this->pos().y() + 50 * qSin((qreal) angle_ * 3.1415926535 / 180);
    QPointF fuite = QPointF(x,y);
    return fuite;
}
