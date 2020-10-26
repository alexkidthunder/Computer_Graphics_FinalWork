#include "boss.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "game.h"

extern Game * game;

Boss::Boss(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    // Set random position X
    int random_number = rand() % 600;
    setPos(random_number,0);

    // Drew the enemy
    setPixmap(QPixmap(":/images/enemy2.png"));
    // Image rotation
    setTransformOriginPoint(50,50);
    setRotation(180);

    // Timer to move the enemy
    QTimer * timer = new QTimer(this);
    connect( timer,SIGNAL(timeout()), this , SLOT(move()));

    // Timer Start
    timer->start(160);
}

void Boss::move(){

    // Move enemy
    setPos( x( ), y()+5 );

    // Destroy enemy out of the screen
    if ( pos().y() > 600 ){
        // Decrease health
        game->health->decrease();
        // Remove enemy
        scene()->removeItem(this);
        delete this;
    }
}

