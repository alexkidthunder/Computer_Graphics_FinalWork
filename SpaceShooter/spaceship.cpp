#include "spaceship.h"

spaceship::spaceship()
{
    this->life_ = 100;
    maxX = 15;
    minX = 0;
    maxY = 15;
    minY = 0;
    maxZ = 15;
    minZ = 0;
}

spaceship::~spaceship()
{
}

void spaceship::privateInit()
{
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);	//begin new list

    glColor3f(0.0f, 0.0f, 1.0f);
    float size = 5.0f;

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size); vertexArray_.push_back(std::vector<float>{ -size, -size, size});
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size); vertexArray_.push_back(std::vector<float>{size, -size, size});
    glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size); vertexArray_.push_back(std::vector<float>{ size, size, size});
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size); vertexArray_.push_back(std::vector<float>{-size, size, size});
    glEnd();

    glEndList();//end new list

}
void spaceship::privateRender()
{
    glCallList(list_id);
}

void spaceship::privateUpdate()
{
}

void spaceship::getSpaceShipPosition()
{
}


float spaceship::getRadius() const
{
    auto eps = 1e-5;

    float centX1, centY1, radius;

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

float spaceship::getLife()
{
    return this->life_;
}

void spaceship::setLife()
{
    this->life_ -= 1;
}
