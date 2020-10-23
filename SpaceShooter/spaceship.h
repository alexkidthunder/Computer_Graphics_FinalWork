#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "bullet.h"
#include <GL/gl.h>
#include <GL/glu.h>

class spaceship
{
public:
    spaceship();
    ~spaceship();
    int list_id;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBackward();
    void moveForward();

    float getPos() const;/**/
    float getRadius() const;

    bool shoot();
    float getLife();
    void setLife();

    float maxX;
    float minX;
    float maxY;
    float minY;
    float maxZ;
    float minZ;

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();
    void getSpaceShipPosition();

private:
    float speed_;
    float life_;

    std::vector< std::vector<float>> vertexArray_;
};

#endif // SPACESHIP_H
