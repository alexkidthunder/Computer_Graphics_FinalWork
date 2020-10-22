#include "glwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>
#include <math.h>

// Constructor
GLWidget::GLWidget() {
    setWindowTitle("SpaceShooter");

    lightChanged = false;
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

// Destructor
GLWidget::~GLWidget() {
    glDeleteTextures(1, &_textureShip);
    glDeleteTextures(1, &_textureSky);
    glDeleteTextures(1, &_textureP);

}

// Initialize OpenGL
void GLWidget::initializeGL() {
    glShadeModel(GL_SMOOTH);    // Enable smooth shading
    qglClearColor(Qt::black);   // Set the clear color to a black background

    glClearDepth(1.0f);      // Depth buffer setup
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);  // Set type of depth-test

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really nice perspective calculations corrections

    glMatrixMode(GL_PROJECTION);// To operate on the Projection matrix
    glLoadIdentity(); // Reset

    glEnable(GL_TEXTURE_2D); // Habilitar TEXTURE 2D

    // Upload images
    QImage img;        
    img = convertToGLFormat(QImage("sand.bmp"));
    _textureShip = loadTexture(img);
    img = convertToGLFormat(QImage("space.bmp"));
    _textureSky = loadTexture(img);
    img = convertToGLFormat(QImage("moontexture.bmp"));
    _textureP = loadTexture(img);

    // Set up lighting
    GLfloat ambLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = {0.0f, 0.0f, 2.0f, 1.0f};
    // Add ambient lighting
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffLight);
    // Add positioned lighting
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}

// This is called when the OpenGL window is resized
void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset
    // Perspective projection: ( fovy, aspect, near, far )
    gluPerspective(60.0f, static_cast<GLfloat>(width)/height, 0.1f, 100.0f); // Calculate the aspect ratio
    glMatrixMode(GL_MODELVIEW);  // To operate on model-view matrix
    glLoadIdentity(); // Reset
}

// OpenGL painting code goes here
void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Reset


    // Design the environment

    // Sky
    glPushMatrix(); // Isolate the Sky withglPushMatriz
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTranslatef(0,0,-100);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-150,150,1);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(150,150,1);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(150,-150,0);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-150,-150,0);
        glEnd();
    glPopMatrix();

    // Base location
    glTranslatef(0 + _distance,-8,-18);  //  Displacement in (x,y,z)
    //glRotatef(_angle, 0.0, 2.0, 0.0);   //  Rotation in (angulo, x, y ,z)
    //glScalef(2.0,2.0,2);  //  Scale in (x,y,z)

    /*
    // Draw the Sand
    glBindTexture(GL_TEXTURE_2D, _textureShip);
    glBegin(GL_QUADS);
        glTexCoord3f(0.0,70.0,1);   glVertex3f(-150,-1.5,25);
        glTexCoord3f(0.0,0.0,-1);   glVertex3f(-150,-1.5,-25);
        glTexCoord3f(70.0,0.0,-1);  glVertex3f(150,-1.5,-250);
        glTexCoord3f(70.0,70.0,1);  glVertex3f(150,-1.5,250);
    glEnd();
*/

    // Design the object

    drawCube();

    // Framerate control
    timer->start(15);
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
    case Qt::Key_Up: // Left Button
        _angle -= 1;
        if (_angle > 360)
            _angle = 0.0;
        break;
    case Qt::Key_Down: // Right Button
        _angle += 1;
        if (_angle > 360)
            _angle = 0.0;
        break;
    case Qt::Key_Right: // Up Button
        _distance += 1;
        break;
    case Qt::Key_Left: // Down Button
        _distance -= 1;
        break;
    case Qt::Key_Space: // Down Button
        drawCube();
        break;

    case Qt::Key_L: // LIGHTING    ON / OFF
        if (glIsEnabled(GL_LIGHTING))
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);
        lightChanged = true;
        break;

    default:
        QGLWidget::keyPressEvent(event); // Let base class handle the other keys
    }
}

// Event handler
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


// Draw cube handler
void GLWidget::drawCube()
{
    glBindTexture(GL_TEXTURE_2D, _textureP);
    // Front side
    glBegin(GL_QUADS);  // Face
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-0.5,0,0.5);
        glTexCoord3f(4.0,2.0,0.1);  glVertex3f(0.5,0,0.5);
        glTexCoord3f(4.0,0.0,0.1);  glVertex3f(0.5,-1,0.5);
        glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-0.5,-1,0.5);
    glEnd();

    // Back side
    glBegin(GL_QUADS);  // Face
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord3f(0.0,2.0,-1);   glVertex3f(-0.5,0,-0.5);
        glTexCoord3f(4.0,2.0,-1);   glVertex3f(0.5,0,-0.5);
        glTexCoord3f(4.0,0.0,-1);   glVertex3f(0.5,-1,-0.5);
        glTexCoord3f(0.0,0.0,-1);   glVertex3f(-0.5,-1,-0.5);
    glEnd();

    // Left side
    glBegin(GL_QUADS);  // Face
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord3f(0.0,2.0,1);    glVertex3f(-0.5,0,0.5);
        glTexCoord3f(2.0,2.0,-1);   glVertex3f(-0.5,0,-0.5);
        glTexCoord3f(2.0,0.0,-1);   glVertex3f(-0.5,-1,-0.5);
        glTexCoord3f(0.0,0.0,1);    glVertex3f(-0.5,-1,0.5);
    glEnd();

    // Right side
    glBegin(GL_QUADS);  // Face
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord3f(0.0,2.0,1);    glVertex3f(0.5,0,0.5);
        glTexCoord3f(2.0,2.0,-1);   glVertex3f(0.5,0,-0.5);
        glTexCoord3f(2.0,0.0,-1);   glVertex3f(0.5,-1,-0.5);
        glTexCoord3f(0.0,0.0,1);    glVertex3f(0.5,-1,0.5);
    glEnd();

    // Upper side     // Ceiling
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 2.0f, 0.0f);
        glTexCoord3f(0.0,2.0,1);    glVertex3f(-0.5,0,0.5);
        glTexCoord3f(2.0,2.0,-1);   glVertex3f(-0.5,0,-0.5);
        glTexCoord3f(2.0,0.0,-1);   glVertex3f(0.5,0,-0.5);
        glTexCoord3f(0.0,0.0,1);    glVertex3f(0.5,0,0.5);
    glEnd();
}

// Texture handler
GLuint GLWidget::loadTexture(QImage image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                  //Always GL_TEXTURE_2D
                 0,                              //0 for now
                 GL_RGBA,                        //Format OpenGL uses for image
                 image.width(), image.height(),  //Width and height
                 0,                              //The border of the image
                 GL_RGBA, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 image.bits());                  //The actual pixel data
    return textureId; //Returns the id of the texture
}
