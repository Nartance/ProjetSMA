#ifndef MAIN_HPP
#define MAIN_HPP

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <iostream>

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QTextStream>

#include "Editeur.hpp"
#include "Mur.hpp"
#include "Porte.hpp"
#include "Assassin.hpp"
#include "Cible.hpp"
#include "Normal.hpp"

QPointF reverseCoord(const QPointF &);
void ajouterTL(std::priority_queue<qreal, std::vector<qreal>, std::greater<qreal> > &, const QPointF&, const QPointF&, const qreal&);
void construire1mur(QGraphicsScene *, const int&,
                    const QPointF&,
                    const QPointF&,
                    const QPointF&,
                    const QPointF&,
                    const QPointF&,
                    const QPointF&);
void creer_limites(QGraphicsScene *);
void creer_murs(QGraphicsScene *, const QPointF&, const QPointF&);
void installer_personnage(QGraphicsScene *);

QTextStream& operator<<( QTextStream& o, const QGraphicsItem * pQGI);



#endif // MAIN_HPP
