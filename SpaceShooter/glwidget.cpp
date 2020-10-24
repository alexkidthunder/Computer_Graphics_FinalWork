#include "glwidget.h"
#include "fstream"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>
#include <math.h>
#include <QDebug>

// Constructor
GLWidget::GLWidget() {
    setWindowTitle("SpaceShooter");
    init_fdata();
    lightChanged = false;
    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

// Destructor
GLWidget::~GLWidget() {
    glDeleteTextures(1, &_textureP);
    glDeleteTextures(1, &_textureSky);
    glDeleteTextures(1, &_textureShip);
}

// *************************** Screen Initialization *********************************

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
    img = convertToGLFormat(QImage("texture/galagasky.bmp"));
    _textureP= loadTexture(img);
    img = convertToGLFormat(QImage("texture/space.bmp"));
    _textureSky = loadTexture(img);
    img = convertToGLFormat(QImage("texture/moontexture.bmp"));
    _textureShip = loadTexture(img);

    // Set up lighting
    GLfloat ambLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat diffLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = {10.0f, 10.0f, 60.0f, 1.0f};
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
    // Perspective projection:(fovy, aspect, near, far),Calculate the aspect ratio
    gluPerspective(60.0f, static_cast<GLfloat>(width)/height, 0.1f, 100.0f);
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
    //glTranslatef(0,-2,-70 + _distance);  //  Displacement in (x,y,z)
    glTranslatef(0 + _Hdistance,-8/*+_angle*/,-18+_Vdistance);// Displacement(x,y,z)
    glRotatef(_angle, 0.0, 2.0, 0.0);   //  Rotation in (angulo, x, y ,z)
    //glScalef(2.0,2.0,2);  //  Scale in (x,y,z)

    // Draw the Floor
    glBindTexture(GL_TEXTURE_2D, _textureP);
    glBegin(GL_QUADS);
        glTexCoord3f(0.0,70.0,1);   glVertex3f(-150,-1.5,25);
        glTexCoord3f(0.0,0.0,-1);   glVertex3f(-150,-1.5,-25);
        glTexCoord3f(70.0,0.0,-1);  glVertex3f(150,-1.5,-250);
        glTexCoord3f(70.0,70.0,1);  glVertex3f(150,-1.5,250);
    glEnd();

    // Design the object

    displayListHandle = glGenLists(1);
    // Start recording the new display list.
    glNewList(displayListHandle, GL_COMPILE);
    // Render a single cube
    drawCube();
    // End the recording of the current display list.
    glEndList();

    //Single cube
    drawCube();

    // Framerate control
    timer->start(60);
}

// **************************** Handlers *********************************

// Key handler
void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        close(); // Quit on Escape
        break;
    case Qt::Key_F1:
        // Toggle fullscreen on F1
        setWindowState(windowState() ^ Qt::WindowFullScreen);
        break;
    case Qt::Key_A: // A Button
        _angle -= 1;
        if (_angle > 360)
            _angle = 0.0;
        break;
    case Qt::Key_D: // D Button
        _angle += 1;
        if (_angle > 360)
            _angle = 0.0;
        break;
    case Qt::Key_Left: // Left Button
        _Hdistance -= 1;
        break;
    case Qt::Key_Right: // Right Button
        _Hdistance += 1;
        break;
    case Qt::Key_Up: // Up Button
        _Vdistance -= 1;
        break;
    case Qt::Key_Down: // Down Button
        _Vdistance += 1;
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



// **************************** Texture handler *********************************

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


// ************************************ Draw ************************************

void GLWidget::drawCube()
{
    glBindTexture(GL_TEXTURE_2D, _textureShip);
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

// ********************************* Obj Loader ***********************************
void GLWidget::init_fdata()
{
std::ifstream ifile("ship/drmyogl1vqc1.obj");
    while(ifile.good()){
        fdata.push_back(ifile.get());
    }

    ifile.close();
    init_vertex();
}

void GLWidget::init_vertex()
{
    std::string line;
    std::getline(fdata, line);
}
