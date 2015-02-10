#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <time.h>
#include <queue>
#include <vector>

#include <QtGlobal>
#include <QtCore/qmath.h>

#include <QApplication>
#include <QFile>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include <QVector4D>

typedef std::vector< std::vector < int > > matInt ;

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
