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
    float getRadius() const;
    void createEnemy();
    bool shoot();

    float maxX;
    float minX;
    float maxY;
    float minY;
    float maxZ;
    float minZ;

    float speed_;
    float life_;
    bool isActive = true;

public slots:
    void move();

private:
    float _positionx = 0.0;
    float _positiony = 0.0;
    float _positionz = 0.0;
    bool friendly_;
        int depth_;


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

    void createBullets();
};

#endif // ENEMY_H
