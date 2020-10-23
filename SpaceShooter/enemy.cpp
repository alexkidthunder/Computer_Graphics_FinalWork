#include "enemy.h"
#include <QTimer>

enemy::enemy(float speed, int xBoundary, float startPos)
{
    this->xBoundary_ = xBoundary;
    this->xPos_ = std::abs(xBoundary_ / 2);
    this->startPos_ = startPos * -1;

    maxX = 7;
    minX = 0;
    maxY = 7;
    minY = 0;
    maxZ = startPos_ + 7;
    minZ = startPos_;

    privateInit();
}

enemy::~enemy()
{
}

std::vector<std::vector<float>> enemy::getVertexArr()
{
    return vertexArray_;
}

bool enemy::getEnemyStatus()
{
    return isActive;
}

float enemy::getPos() const
{
    return this->posit_x;
}

float enemy::getRadius() const
{
    auto eps = 1e-5;

    float centX1, centY1, centZ1, radius;

    if ((minX + maxX) / 2 < eps) centX1 = 0;
    else centX1 = (minX + maxX) / 2;

    if ((minY + maxY) / 2 < eps) centY1 = 0;
    else centY1 = (minY + maxY) / 2;

    float distanceX1 = 0.0f;
    float xVarMax1 = std::abs(maxX) - std::abs(centX1);
    float xVarMin1 = std::abs(minX) - std::abs(centX1);

    if (xVarMax1 > xVarMin1) distanceX1 = xVarMax1;
    else distanceX1 = xVarMin1;

    float distanceY1 = 0.0f;
    float yVarMax1 = std::abs(maxY) - std::abs(centY1);
    float yVarMin1 = std::abs(minY) - std::abs(centY1);

    if (yVarMax1 > yVarMin1) distanceY1 = yVarMax1;
    else distanceY1 = yVarMin1;

    if (distanceX1 > distanceY1) radius = distanceX1;
    else radius = distanceY1;

    return radius;
}

void enemy::createEnemy()
{
    glColor3f(color_[0], color_[1], color_[2]);
    float size = 5.0f;

    glBegin(GL_QUADS);
    glNormal3f(5.0f, 5.0f, -50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, startPos_);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, startPos_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, startPos_);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, startPos_);

    glEnd();
}

bool enemy::shoot()
{
    if (isActive) {
        return true;
    }
    return false;
}

void enemy::privateInit()
{
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    createEnemy();
    glEndList();

    //myModel1 = std::make_shared<Model>("../Models/1.blend");
    //myModel1->Import3DFromFile();
}

void enemy::privateRender()
{
    glCallList(list_id);
    glFlush();

    //	myModel1->DrawGLScene();

}

void enemy::privateUpdate()
{
    //move object
    float max_x = xBoundary_;
    float min_x = xBoundary_*-1;

   // matrix_ = (xPos_, max_y, (speed_*0.5f) * z_coord);

    // Z-direction
    z_coord++;

    // X-direction
    if (checkFlag == false) xPos_++;
    else xPos_--;

    if (xPos_ == max_x) checkFlag = true;
    if (xPos_ == min_x) checkFlag = false;

}


