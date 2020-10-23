#ifndef BULLET_H
#define BULLET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <QObject>

class bullet
{
public:
    bullet( float/**/ position, bool friendly, int depth);
    ~bullet();
    float getPosition();/* */

    int life_;
    int bullets;
    /*
     * std::vector< std::vector<float>> getVertexArr();
    */
    float getPos() const;/* */
    float getRadius() const;

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

    void createBullets();

private:
    std::string type_;
    float position_;/* */
    bool friendly_;
    int depth_;


    float maxX;
    float minX;
    float maxY;
    float minY;
    float maxZ;
    float minZ;


    std::vector< std::vector<float>> vertexArray_; //vertex array

};


#endif // BULLET_H
