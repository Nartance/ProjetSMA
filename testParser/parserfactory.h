#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include "main.hpp"
#include "Mur.hpp"
#include "Assassin.hpp"
#include "Cible.hpp"
#include "Normal.hpp"
#include "Surveillant.hpp"

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
