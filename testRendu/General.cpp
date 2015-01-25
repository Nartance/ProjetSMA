#include "General.hpp"

qreal normalise_angle(qreal angle)
{
    while(angle < 0)
        angle += 360;
    while(angle > 360)
        angle -= 360;
    return angle;
}

QPoint change_repere(QPoint point)
{
    return QPoint(point.x() + 50, point.y() + 50);
}

void afficher_QPointF(QPointF point)
{
    std::cout << "(" << point.x() << ";" << point.y() << ")" << std::endl;
}

void afficher_QRectF(QRectF rect)
{
    std::cout << "TopLeft : ";
    afficher_QPointF(rect.topLeft());

    std::cout << "BottomRight : ";
    afficher_QPointF(rect.bottomRight());
}
