#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // Put the health to 3
    health = 3;

    // Draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",20));
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
}

int Health::getHealth()
{
    return health;
}
