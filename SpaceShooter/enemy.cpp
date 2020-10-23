#include "enemy.h"
#include <QTimer>

enemy::enemy()
{
    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}

void enemy::move(){
    this->_positionx;

    // if there was no collision with an Enemy, move the bullet forward
    setPos(x(),y()-10);
    // if the bullet is off the screen, destroy it
    if (pos().y() + rect().height() < 0){
        scene()->removeItem(this);
        delete this;
    }
    float enemy::getposition(){
        this->_positionx;
    }
void enemy::privateInit()
    {
        bullets = glGenLists(1);
        glNewList(bullets, GL_COMPILE);
        createBullets();
        glEndList();
    }
}
