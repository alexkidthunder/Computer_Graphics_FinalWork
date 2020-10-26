#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // Put the health to 4
    health = 4;

    // Draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 4
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",20));
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3...
}

int Health::getHealth()
{
    return health;
}

void Health::Gameover()
{
    // Draw the text
    setPlainText(QString(" Game Over ")); // Game Over
    setDefaultTextColor(Qt::red);
    setPos(270,270);
    setFont(QFont("times",40));
}
