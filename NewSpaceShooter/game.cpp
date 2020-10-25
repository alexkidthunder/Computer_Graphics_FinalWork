#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "enemy.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

Game::Game(QWidget *parent){

    // Create Scene
    scene = new QGraphicsScene();
    scene->setSceneRect( 0, 0, 800, 600 ); // Make the scene 800x600
    // Set the Background
    setBackgroundBrush(QBrush(QImage(":/images/floor.png")));

    // Make scene the scene to visualize.
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // Create the player
    player = new Player();
    player->setPos(400,500);// Generalize to always be in the middle bottom

    // Make the player be the focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Add the player
    scene->addItem(player);

    // Create and add the score and health
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);

    // Test Game over
    if (health->getHealth() == 0) {
        scene->removeItem(player);
        delete player;
    }

    // Spawn enemies with time
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);

    // Play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();// Loop
    playlist->addMedia(QUrl("qrc:/bg.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer * music = new QMediaPlayer();
    //music->setMedia(QUrl("qrc:/bg.wav"));// Single Play
    music->setPlaylist(playlist);// Config Loop
    music->setVolume(26);
    music->play(); // Play

    show();
}
