#include "bullet.h"

bullet::bullet(float position/**/, bool friendly, int depth)
{
    this->position_ = position;
    this->friendly_ = friendly;
    this->depth_ = depth;
    this->maxX = 7;
    this->minX = 0;
    this->maxY = 7;
    this->minY = 0;
    this->maxZ = position_ - 7;/**/
    this->minZ = position_;/**/

    privateInit();
}
bullet::~bullet()
{
}

float getPosition()
{
    return position_;
}

std::vector< std::vector<float>> bullet::getVertexArr()
{
    return vertexArray_;
}


void bullet::privateInit()
{
    bullets = glGenLists(1);
    glNewList(bullets, GL_COMPILE);
    createBullets();
    glEndList();
}

void bullet::privateRender()
{

    glCallList(bullets);
    glFlush();
}

void bullet::privateUpdate()
{
    if (friendly_ == true)
        /*matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -7.0f));
    else
        matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 7.0f));
        */
    life_--;
}

void bullet::createBullets()
{

    auto x = position_.x;
    auto y = position_.y;
    auto z = position_.z;

    if (friendly_ == false)
        z = -depth_ + position_.z;

    float increment;
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    //glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(x + increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y + increment, z + increment});
    glVertex3f(x - increment, y + increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y + increment, z + increment});
    glVertex3f(x - increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x - increment, y - increment, z + increment});
    glVertex3f(x + increment, y - increment, z + increment); vertexArray_.push_back(std::vector<float>{x + increment, y - increment, z + increment});
    glEnd();

}

float bullet::getPos() const
{
    return glm::vec3(position_[0], position_[1], matrix_[3][2]);
}


float bullet::getRadius() const
{
    auto eps = 1e-5;

    float centX1, centY1, centZ1, radius;

    if ((minX + maxX) / 2 < eps) centX1 = 0;
    else centX1 = (minX + maxX) / 2;

    if ((minY + maxY) / 2 < eps) centY1 = 0;
    else centY1 = (minY + maxY) / 2;
    /******************************************************************************************/
    //if ((zMin + zMax) / 2 < eps) centY = 0;
    //else centZ = (zMin + zMax) / 2;

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
