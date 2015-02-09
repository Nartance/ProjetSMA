#ifndef GENERAL_HPP
#define GENERAL_HPP

#include "Mur.hpp"

#include "Assassin.hpp"
#include "Cible.hpp"
#include "Normal.hpp"
#include "Surveillant.hpp"

QPoint change_repere(QPoint);
void afficher_QPointF(QPointF);
void afficher_QRectF(QRectF);

QPointF lire(const QString & filename, QGraphicsScene * scene, matInt & grille);

#endif // GENERAL_HPP
