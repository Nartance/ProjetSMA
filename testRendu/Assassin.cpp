#include "Assassin.hpp"

Assassin::Assassin(const int & angle = 0, bool affichage) : Personnage(angle), affichage_(affichage)
{
    origine_tir_ = QPointF(-10,-10);
    visee_ = NULL;
}

void Assassin::paint(QPainter * painter, const QStyleOptionGraphicsItem * qsogt, QWidget * qw)
{
    painter->setBrush(QBrush(QColor(220,0,0)));
    Personnage::paint(painter, qsogt, qw);
}

void Assassin::type()
{
    std::cout << "Assassin" << std::endl;
}

void Assassin::action(const QList<QGraphicsItem *> & liste_item)
{
    // Modifier en 6 avec l'arrivée des murs avec porte
    QGraphicsItem * cible = liste_item[liste_item.size() - 7];
    angle_ = normalise_angle(360 - QLineF(this->pos(), cible->pos()).angle());

    if(visee_ == NULL)
    {
        visee_ = new QTime();
        visee_->start();
    }

    if(visee_->elapsed() > 5000)
    {
        ((Cible *) cible)->mort();
        origine_tir_ = this->pos();
    }
}

void Assassin::move()
{
    setRotation(angle_);
    setPos(mapToParent(0,0));
}
