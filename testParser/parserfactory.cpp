/*!
 * \file  "ParserFactory.cpp"
 *
 * \brief Fichier contenant la définition des méthodes de la classe réprésentant l'usine du parser de fichier de scène.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
#include "parserfactory.hpp"

/*! \brief Instanciation de l'instance unique */
ParserFactory ParserFactory::_instance = ParserFactory();

/*!
 * \fn  ParserFactory::ParserFactory()
 *
 * \brief Constructeur.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 */
ParserFactory::ParserFactory()
{

}

/*!
 * \fn  ParserFactory::getInstance()
 *
 * \brief Constructeur.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \return Une référence de l'instance unique.
 */
ParserFactory& ParserFactory::getInstance()
{
    return _instance;
}

/*!
 * \fn  QGraphicsItem * ParserFactory::instancierItem(const QString & nom, const QPointF & TL, const QPointF & BR)
 *
 * \brief Instancie un item de la scène selon son nom.
 *
 * \author  Nicolas Artance / David Feraud
 * \date  10/02/2015
 *
 * \param nom ( Entrée ) Nom de l'instance.
 * \param TL ( Entrée ) Le point topleft pour les murs, la position pour les autres items.
 * \param BR ( Entrée ) Le point bottomright pour les murs (inutilisé pour les autres items).
 *
 * \return L'item instancié.
 */
QGraphicsItem * ParserFactory::instancierItem(const QString & nom, const QPointF & TL, const QPointF & BR)
{
    if( nom == "Mur")
        return new Mur(TL, BR);
    else if ( nom == "Normal")
    {
        Normal * n = new Normal(qrand()%360);
        n->setPos(TL);
        return n;
    }
    else if ( nom == "Cible")
    {
        Cible * c = new Cible(qrand()%360);
        c->setPos(TL);
        return c;
    }
    else if ( nom == "Assassin")
    {
        Assassin * a = new Assassin(qrand()%360);
        a->setPos(TL);
        return a;
    }
    else if ( nom == "Surveillant")
    {
        Surveillant * s = new Surveillant(qrand()%360);
        s->setPos(TL);
        return s;
    }

    return NULL ;
}
