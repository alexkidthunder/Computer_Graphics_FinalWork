#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include <QHash>
#include <string>
#include <vector>

class QTimer;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    // constructor
    GLWidget();
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void changeEvent(QEvent *event);

private:
    std::string fdata;
    void drawCube();    
    float _angle = 0.0;
    float _Vdistance = 0.0;
    float _Hdistance = 0.0;
    bool lightChanged;
    int displayListHandle = -1;

    void init_fdata();
    void init_vertex();

    struct coord{
        float x,y,z;
    };
    std::vector<coord> vertex_vec;

    GLuint loadTexture(QImage image);
    QTimer *timer;

    GLuint  _textureShip,
            _textureSky,
            _textureP;

};

#endif // GLWIDGET_H
