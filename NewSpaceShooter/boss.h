#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Boss: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Boss(QGraphicsItem * parent=0);
public slots:
    void move();
};

#endif // BOSS_H
