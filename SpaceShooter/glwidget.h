#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include <QHash>

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
    void drawCube();
    float _angle = 0.0;
    float _distance = 0.0;
    bool lightChanged;
    int displayListHandle = -1;

    GLuint loadTexture(QImage image);
    QTimer *timer;

    GLuint  _textureShip,
            _textureSky,
            _textureP;

};

#endif // GLWIDGET_H
