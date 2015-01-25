#ifndef ALGORITHME_HPP
#define ALGORITHME_HPP

#include "main.hpp"

enum COULEUR
{
    BLANC,
    GRIS,
    NOIR
};
typedef struct Pixel
{
    int niveau;
    COULEUR coul;
}Pixel;

class Editeur
{
public :
    Editeur(const QGraphicsScene *);
    void cartographier();

protected :


private :
    bool verifier_traitement(const QList<QGraphicsItem*>&, const QPointF &);
    void sauver_grille();

    const QGraphicsScene * scene_;
    std::vector<Pixel> grille_;
    int width_;
    int height_;
    int elemSize_;


};

#endif // ALGORITHME_HPP
