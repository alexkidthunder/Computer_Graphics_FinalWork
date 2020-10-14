#include "glwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>

GLfloat fPasso = 1.0f/255.0f;

// Constructor
GLWidget::GLWidget() {
    setWindowTitle("SpaceShooter");
}

// Destructor
GLWidget::~GLWidget() {

}

// Initialize OpenGL
void GLWidget::initializeGL() {
    qglClearColor(Qt::black); // Set the clear color to a black background
}

// This is called when the OpenGL window is resized
void GLWidget::resizeGL(int width, int height) {
    // Prevent divide by zero (in the gluPerspective call)
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height); // Reset current viewport

    glMatrixMode(GL_PROJECTION); // Select projection matrix
    glLoadIdentity(); // Reset projection matrix

    // Estabelece a janela de seleção (esquerda, direita, inferior,
    // superior) mantendo a proporção com a janela de visualização
    if (width <= height)
        gluOrtho2D (-40.0f, 40.0f, -40.0f*height/width, 40.0f*height/width);
    else
        gluOrtho2D (-40.0f*width/height, 40.0f*width/height, -40.0f, 40.0f);
}

// OpenGL painting code goes here
void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and depth buffer

    glLoadIdentity(); // Reset current modelview matrix

    glColor3f(corVermelho,corVerde,corAzul);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,  -0.8f, 0.f);
        glVertex3f(0.07f,-0.9f, 0.f);
        glVertex3f(-0.07f, -0.9f, 0.f);
    glEnd();

}

// Key handler
void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        close(); // Quit on Escape
        break;
    case Qt::Key_F1:
        setWindowState(windowState() ^ Qt::WindowFullScreen); // Toggle fullscreen on F1
        break;
    case Qt::Key_A:
        (corVermelho>=1)?corVermelho=1:corVermelho+=fPasso;
        break;
    case Qt::Key_Z:
        (corVermelho<=0)?corVermelho=0:corVermelho-=fPasso;
        break;
    case Qt::Key_S:
        (corVerde>=1)?corVerde=1:corVerde+=fPasso;
        break;
    case Qt::Key_X:
        (corVerde<=0)?corVerde=0:corVerde-=fPasso;
        break;
    case Qt::Key_D:
        (corAzul>=1)?corAzul=1:corAzul+=fPasso;
        break;
    case Qt::Key_C:
        (corAzul<=0)?corAzul=0:corAzul-=fPasso;
        break;
    default:
        QGLWidget::keyPressEvent(event); // Let base class handle the other keys
    }

    QString strSpaceShooter;
    strSpaceShooter.append("TesteAba:"); strSpaceShooter.append(" R:");
    strSpaceShooter.append(QString::number(corVermelho)); strSpaceShooter.append(" G:");
    strSpaceShooter.append(QString::number(corVerde)); strSpaceShooter.append(" B:");
    strSpaceShooter.append(QString::number(corAzul));
    setWindowTitle(strSpaceShooter);

    updateGL();
}

void GLWidget::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::WindowStateChange:
        // Hide cursor if the window is fullscreen, otherwise show it
        if (windowState() == Qt::WindowFullScreen)
            setCursor(Qt::BlankCursor);
        else if (windowState() == Qt::WindowMaximized) {
            update();
        }
        else
            unsetCursor();
        break;
    default:
        break;
    }
}
