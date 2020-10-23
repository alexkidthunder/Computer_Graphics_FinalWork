#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <GL/gl.h>
#include <GL/glu.h>

class enemy:  public QObject{
    Q_OBJECT

public:
    enemy(float speed, int xBoundary, float startPos);
        ~enemy();

    int list_id;
    std::vector< std::vector<float>> getVertexArr();
    GLuint vertexbuffer;

    bool getEnemyStatus();// if enemy status is not active - erase enemy from the scene
    float getPos() const;
    float getRadius() const;
    void createEnemy();
    bool shoot();

    float maxX;
    float minX;
    float maxY;
    float minY;
    float maxZ;
    float minZ;
    float posit_x;
    float posit_y;
    float posit_z;

    float speed_;
    float life_;
    bool isActive = true;

protected:
        void privateInit();
        void privateRender();
        void privateUpdate();

private:
    std::string type_;

    float startPos_;

    bool checkFlag = false;
    float max_z = 50.0;
    float min_z = -150.0;

    float max_y = 10.0;
    float min_y = 0.0;

    int z_coord = 0;
    double y_coord = 0.0;

    std::vector< std::vector<float>> vertexArray_; //vertex array
    std::vector<float> color_;

    int xBoundary_;
    int xPos_;
};

#endif // ENEMY_H
