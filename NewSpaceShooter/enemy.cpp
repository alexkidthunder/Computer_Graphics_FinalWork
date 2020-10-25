#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // Set random position X
    int random_number = rand() % 700;
    setPos( random_number , 0 );

    // Drew the rect
    setPixmap(QPixmap(":/images/enemy1.png"));

    // Timer to move the enemy
    QTimer * timer = new QTimer(this);
    connect( timer,SIGNAL( timeout() ),this,SLOT( move() ));

    // Timer Start
    timer->start(60);
}

void Enemy::move(){
    // Move enemy down
    setPos (x() , y()+5 );

    // Destroy enemy out of the screen
    if ( pos().y() > 600 ){
        // Decrease health
        game->health->decrease();
        // Remove enemy
        scene()->removeItem(this);
        delete this;
    }
}

