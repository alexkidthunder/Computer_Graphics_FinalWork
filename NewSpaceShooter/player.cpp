#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"
#include "boss.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // Set the music media
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/pew.wav"));
    bulletsound->setVolume(30);

    // Set graphic
    setPixmap(QPixmap(":/images/ship01.png"));
}

// Key handler
void Player::keyPressEvent(QKeyEvent *event){
    // Move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
            setPos(x()+10,y());
    }
    // Spacebar to Shoot
    else if (event->key() == Qt::Key_Space){

        // Create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);

        // play bullet sound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}

// Spawn
void Player::spawn(){

    // Create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
    Boss * boss = new Boss();
    // Add the enemy
    scene()->addItem(boss);
}
