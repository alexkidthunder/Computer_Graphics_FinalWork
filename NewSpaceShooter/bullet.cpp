#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "enemy.h"
#include "boss.h"
#include "game.h"

extern Game * game; // External global object game

Bullet::Bullet(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent){
    // Drew the bullet
    //setRect(45,-30,15,15); // Literaly draw
    setPixmap(QPixmap(":/images/bullet.png"));
    setPos(x()+15,y()+15);


    // Make a timer to move the bullet
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // Start the timer
    timer->start(50);
}

void Bullet::move(){
    // Get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // If one of the colliding items is an Enemy, destroy both
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            // Increase the score
            game->score->increase();

            // Remove from the scene
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // Delete them from the heap
            delete colliding_items[i];
            delete this;

            // Return
            return;
        }
        else if (typeid(*(colliding_items[i])) == typeid(Boss)) {
            // Increase the score
            game->score->increase();

            // Remove from the scene
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // Delete them from the heap
            delete colliding_items[i];
            delete this;

            // Return (all code below refers to a non existint bullet)
            return;
        }
    }

    // No collision with an Enemy, move the bullet
    setPos(x(),y()-10);
    // if the bullet is off the screen, destroy the bullet
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
