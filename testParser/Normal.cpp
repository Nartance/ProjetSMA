#include "Normal.hpp"

Normal::Normal(const int & angle, bool affichage) : Personnage(angle), affichage_(affichage)
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
    QGraphicsItem * assassin = liste_item[10];

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
            {
                panique_ = true;
                vitesse_deplacement_ = 1;

                // RECODER LA PANIQUE

                int x = abs(this->pos().x()) - 50;
                int y = abs(this->pos().y()) - 50;

                int position = grille_[x][y];

                if(x <= grille_.size() && position > grille_[x+1][y] && grille_[x+1][y] > -1)
                    angle_ = 0;

                if(y <= grille_[0].size() && position > grille_[x][y+1] && grille_[x][y+1] > -1)
                    angle_ = 90;

                if(position > grille_[x-1][y] && grille_[x-1][y] > -1)
                    angle_ = 180;

                if(position > grille_[x][y-1] && grille_[x][y-1] > -1)
                    angle_ = 270;

                if(affichage_)
                    std::cout << grille_[x][y] << std::endl;
            }
        }
    }
}

void Normal::move()
{
    setRotation(angle_);
    setPos(mapToParent(vitesse_deplacement_,0));
}
