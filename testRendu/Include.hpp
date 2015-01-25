#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <algorithm>

#include <QtGlobal>
#include <QtCore/qmath.h>

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QTime>
#include <QTimer>

class minimum_distance_QLineF
{
public :
    minimum_distance_QLineF() {}
    bool operator() (const QLineF & l1, const QLineF & l2)
    {
        return (l1.length() < l2.length());
    }
};

qreal normalise_angle(qreal);

#endif // INCLUDE_HPP
