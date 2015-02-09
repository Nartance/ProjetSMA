#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include "main.hpp"

class ParserFactory
{
private:
    static ParserFactory _instance;
    ParserFactory();
public:

    static ParserFactory& getInstance();
    QGraphicsItem * instancierItem(const QString &, const QPointF &, const QPointF &);
};

#endif // PARSERFACTORY_H
