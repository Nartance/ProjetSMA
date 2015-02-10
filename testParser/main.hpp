#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <exception>
#include <map>

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "parserfactory.hpp"

/*! \brief Type pour la map d'élévation */
typedef std::vector< std::vector < int > > matInt ;

/*! \brief Parse le fichier passé en paramètre */
void parser( const QString &, QGraphicsScene *, matInt &grille );

#endif // MAIN_HPP
