#include "Normal.hpp"

Normal::Normal(const int & angle = 0, bool affichage) : Personnage(angle), affichage_(affichage)
{
    vitesse_deplacement_ = vitesse_;
    panique_ = false;
    pause_ = NULL;


    temps_ = 0;
    angle_arret_ = 0;
}

void Normal::paint(QPainter * painter, const QStyleOptionGraphicsItem * qsogt, QWidget * qw)
{
    painter->setBrush(QBrush(QColor(220,220,220)));
    Personnage::paint(painter, qsogt, qw);
}

void Normal::type()
{
    std::cout << "Normal" << std::endl;
}

void Normal::action(const QList<QGraphicsItem *> & liste_item)
{
    QGraphicsItem * assassin = liste_item[liste_item.size() - 5];

    if(((Assassin *) assassin)->origine_tir_ != QPointF(-10,-10))
    {
        QPointF origine = ((Assassin *) assassin)->origine_tir_;
        vitesse_deplacement_ = 0;

        if(pause_ == NULL)
        {
            pause_ = new QTime();
            pause_->start();

            qreal valeur = normalise_angle((QLineF(this->pos(), origine)).angleTo(QLineF(this->pos(),regard())));
            qreal signe = valeur < 180 ? 1 : -1;

            if(valeur > 180)
                valeur -= 180;

            temps_ = signe * valeur * 5000 / 180;
            angle_arret_ = angle_;

            std::cout << temps_ << std::endl;
        }

        if(pause_->elapsed() < abs(temps_))
        {
            vitesse_deplacement_ = (vitesse_ - (vitesse_ / 1000) * pause_->elapsed() > 0)
                    ? vitesse_ - (vitesse_ / 1000) * pause_->elapsed()
                    : 0;

            angle_ = angle_arret_ + ((qreal) temps_ / abs(temps_)) * ((qreal) 180 / 5000) * pause_->elapsed();
        }
        else
        {
            // PANIQUE
            if(pause_->elapsed() > 5000)
                panique_ = true;
        }
    }
}

void Normal::move()
{
    if(!panique_)
    {
        setRotation(angle_);
        setPos(mapToParent(vitesse_deplacement_,0));
    }
    else
    {
        setRotation(angle_);
        setPos(mapToParent(vitesse_deplacement_,0));
    }
}
