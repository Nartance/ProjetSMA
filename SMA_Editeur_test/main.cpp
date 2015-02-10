#include "Editeur.hpp"

int hauteur_ = 400;
int largeur_ = 400;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QGraphicsScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.setBackgroundBrush(QBrush(QColor(255,255,255)));
    scene.setSceneRect(QRect(0,0,largeur_ + 100,hauteur_ + 100));
    scene.addRect(QRect(50,50,largeur_,hauteur_), QPen(QColor(255,255,255)), QBrush(QColor(255,255,255)));

    Editeur map(&scene);

    map.creer_limites(&scene);
    map.installer_personnage(&scene);
    map.cartographier();

    // Appel de la vue

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QBrush(QColor(220,220,220)));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Test d'algo"));
    view.show();

    return app.exec();
}

