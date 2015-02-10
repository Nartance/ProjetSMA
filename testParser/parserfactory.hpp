/*!
 * \file  "ParserFactory.hpp"
 *
 * \brief Fichier contenant la déclaration des méthodes de la classe réprésentant l'usine du parser de fichier de scène.
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */

#ifndef PARSERFACTORY_HPP
#define PARSERFACTORY_HPP

#include "main.hpp"
#include "Mur.hpp"
#include "Assassin.hpp"
#include "Cible.hpp"
#include "Normal.hpp"
#include "Surveillant.hpp"

/*!
 * \class PaserFactory
 *
 * \brief Usine pour le parseur de fichier
 *
 * \author Nicolas ARTANCE / David FERAUD
 * \date 10/02/2015
 * \version 1
 */
class ParserFactory
{
private:
    /*! \brief Instance unique */
    static ParserFactory _instance;

    /*! \brief Constructeur */
    ParserFactory();
public:

    /*! \brief Accès à l'instance unique */
    static ParserFactory& getInstance();

    /*! \brief Instancie un item de la scène selon un fichier */
    QGraphicsItem * instancierItem(const QString &, const QPointF &, const QPointF &);
};

#endif // PARSERFACTORY_HPP
