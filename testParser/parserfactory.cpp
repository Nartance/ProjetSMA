#include "parserfactory.h"

ParserFactory ParserFactory::_instance = ParserFactory();

ParserFactory::ParserFactory()
{

}

ParserFactory& ParserFactory::getInstance()
{
    return _instance;
}

QGraphicsItem * ParserFactory::instancierItem(const QString & nom, const QPointF & TL, const QPointF & BR)
{
    if( nom == "Mur")
        return new Mur(TL, BR);
    /*else if ( nom == "Normal")
    {
        Normal * n = new Normal(qrand());
        n->setPos(TL);
        return n;
    }
    else if ( nom == "Cible")
    {
        Cible * c = new Cible(qrand());
        c->setPos(TL);
        return c;
    }
    else if ( nom == "Assassin")
    {
        Assassin * a = new Assassin(qrand());
        a->setPos(TL);
        return a;
    }
    else if ( nom == "Surveillant")
    {
        Surveillant * s = new Surveillant(0);
        s->setPos(TL);
        return s;
    }
*/
    return NULL ;
}
