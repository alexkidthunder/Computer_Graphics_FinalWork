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
    void changeEvent(QEvent *event);

private:
    float _angle = 0.0;
    float _Vdistance = 0.0;
    float _Hdistance = 0.0;
    bool lightChanged;

    GLuint loadTexture(QImage image);
    GLuint carregaModelo();

    QTimer *timer;

    GLuint  _textureFloor,
            _textureSky;
};

#endif // GLWIDGET_H
