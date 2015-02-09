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

#include "Mur.hpp"
#include "parserfactory.h"

typedef std::map<QString, std::vector<QGraphicsItem*> > mapType;
typedef std::vector< std::vector < int > > matInt ;

void parser( const QString &, QGraphicsScene *, matInt &grille );

#endif // MAIN_HPP
