#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include <QHash>

class QTimer;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget();// Constructor
    ~GLWidget();// Destructor

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void changeEvent(QEvent *event);
    void spawn(int h, int i, int y);

private:
    float _angleH = 0.0;
    float _angleV = 0.0;
    float _Vdistance = 0.0;
    float _Hdistance = 0.0;
    bool lightChanged;
    int m_xRot= 0.0;
    int m_yRot= 0.0;
    int displayListHandle = -1;

    QPoint m_lastPos;

    GLuint loadTexture(QImage image);
    GLuint loadModel();
    GLuint loadEnemyModel();
    GLuint loadBossModel();

    QTimer *timer;

    GLuint  _textureFloor,
            _textureSky;
};

#endif // GLWIDGET_H
