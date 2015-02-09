#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include "main.hpp"

class ParserFactory
{
public:

    ParserFactory();
    QGraphicsItem * instancierItem(const QString &, const QPointF &, const QPointF &);
};

#endif // PARSERFACTORY_H
