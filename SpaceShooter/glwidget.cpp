#include "glwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>

#include <bullet.h>

// Cor
GLfloat fCor = 5.0f/255.0f;

// Qnt Movimento
GLfloat fmov = .07f;

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

    glTranslatef(direcaoX,direcaoY,0.f);

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
    case Qt::Key_R:
        (corVermelho>=1)?corVermelho=1:corVermelho+=fCor;
        break;
    case Qt::Key_F:
        (corVermelho<=0)?corVermelho=0:corVermelho-=fCor;
        break;
    case Qt::Key_T:
        (corVerde>=1)?corVerde=1:corVerde+=fCor;
        break;
    case Qt::Key_G:
        (corVerde<=0)?corVerde=0:corVerde-=fCor;
        break;
    case Qt::Key_Y:
        (corAzul>=1)?corAzul=1:corAzul+=fCor;
        break;
    case Qt::Key_H:
        (corAzul<=0)?corAzul=0:corAzul-=fCor;
        break;

    case Qt::Key_Right:
        direcaoX+=fmov;
        break;
    case Qt::Key_Left:
        direcaoX-=fmov;
        break;
    case Qt::Key_Up:
        direcaoY+=fmov;
        break;
    case Qt::Key_Down:
        direcaoY-=fmov;
        break;

    case Qt::Key_Space:
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);


    default:
        QGLWidget::keyPressEvent(event); // Let base class handle the other keys
    }

    // Testes Cor e Direcao na aba
    QString strSpaceShooter;
    strSpaceShooter.append(" TesteAba: "); strSpaceShooter.append(" R:");
    strSpaceShooter.append(QString::number(corVermelho)); strSpaceShooter.append(" G:");
    strSpaceShooter.append(QString::number(corVerde)); strSpaceShooter.append(" B:");
    strSpaceShooter.append(QString::number(corAzul));
    setWindowTitle(strSpaceShooter);
    strSpaceShooter.append(" Teste de Translação 2D: ");
    strSpaceShooter.append(" X:");
    strSpaceShooter.append(QString::number(direcaoX));
    strSpaceShooter.append(" Y:");
    strSpaceShooter.append(QString::number(direcaoY));
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
