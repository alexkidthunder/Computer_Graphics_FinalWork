#include "glwidget.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>

extern "C" {
#include "glm.h"
}

// Player, Enemy, Boss models
GLMmodel* pmodel = NULL;
GLMmodel* emodel = NULL;
GLMmodel* bmodel = NULL;
GLMmodel* bulletmodel = NULL;

float _bulletDist = 0.0f;

// Constructor
GLWidget::GLWidget() {
    setWindowTitle("NewSpaceShooter");

    timer = new QTimer(this);
    //timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));

    lightChanged = false;
}

// Destructor
GLWidget::~GLWidget() {
    glDeleteTextures(1, &_textureFloor);
    glDeleteTextures(1, &_textureSky);
}

// **************************** Screen Initialization ************************************

// Initialize OpenGL
void GLWidget::initializeGL() {
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    qglClearColor(Qt::black);// Set the clear color to a black background

    glClearDepth(1.0f);      // Depth buffer setup
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glDepthFunc(GL_LEQUAL);  // Set type of depth test

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really nice perspective calculations

    glMatrixMode(GL_PROJECTION);// To operate on the projection matrix
    glLoadIdentity();        // Reset

    glEnable(GL_TEXTURE_2D); // Habilitar TEXTURE 2D


    // Set up lighting
    GLfloat ambLight[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat diffLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = {10.0f, 10.0f, 60.0f, 1.0f};

    // Add ambient lighting
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffLight);

    // Add positioned lighting
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Enable
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Upload images
    QImage img;
    img = convertToGLFormat(QImage("floor.bmp"));
    _textureFloor = loadTexture(img);
    img = convertToGLFormat(QImage("sky.bmp"));
    _textureSky = loadTexture(img);

    // Upload Object
    if (!pmodel) {
        pmodel = glmReadOBJ("data/ship.obj");
        emodel = glmReadOBJ("data/enemy01.obj");
        bmodel = glmReadOBJ("data/boss01.obj");
        bulletmodel = glmReadOBJ("data/bullet.obj");
        if (!pmodel)
            exit(0);
    }
}

// When the OpenGL window is resized this is called
void GLWidget::resizeGL(int width, int height) {
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);// To operate on the Projection matrix
    glLoadIdentity();           // Reset
    // Perspective projection:(fovy, aspect, near, far),Calculate the aspect ratio
    //gluPerspective(60.0f, static_cast<GLfloat>(width)/height, 0.1f, 100.0f);
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW); // To operate on model-view matrix
    glLoadIdentity();           // Reset
}

// ********************************** Painting ***************************************

// OpenGL painting code
void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Movement in paused clicks, remove for continuous movement
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// Reset

    // Sky texture
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureSky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-80);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-80,80,0);
    glTexCoord3f(1.0,1.0,0.1);  glVertex3f(80,80,0);
    glTexCoord3f(1.0,0.0,0.1);  glVertex3f(80,-80,0);
    glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-80,-80,0);
    glEnd();
    glPopMatrix();

    glTranslatef(_Hdistance,0,_Vdistance);

    // Rotation relative to the view
    glRotatef(m_xRot / 100.0f, 0.0, 1.0, 0.0);
    glRotatef(m_yRot / 100.0f, 1.0, 0.0, 0.0);

    // Floor texture
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, _textureFloor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTranslatef(0,0,-6);
    //glRotatef(_angle, 0.0, 1.0, 0.0);// Rotation relative to the floor
    glBegin(GL_QUADS);
    glTexCoord3f(0.0,70.0,1);  glVertex3f(-50,-1.5,50);
    glTexCoord3f(0.0,0.0,-1);  glVertex3f(-50,-1.5,-50);
    glTexCoord3f(70.0,0.0,-1);  glVertex3f(50,-1.5,-50);
    glTexCoord3f(70.0,70.0,1);  glVertex3f(50,-1.5,50);
    glEnd();
    glPopMatrix();

    //Carrega o Modelo do arquivo .obj
    glPushMatrix();
    //glTranslatef(0 + _Hdistance,0,-6+_Vdistance);
    glTranslatef(0,0,-6);
    //glRotatef(_angle, 0.0, 1.0, 0.0);// Rotation relative to the object
    glRotatef(_angle, 0.9, 0.0, 0.0);
    update();

    loadModel();

    // Configurations
    glTranslatef(0,0,-1.6);
    glScalef(0.25,0.25,0.25);
    glTranslatef(0,-0.5,_bulletDist);

    loadBulletModel();

    glPopMatrix();

    // Put models in list

    listHandleDisp = glGenLists(1);
    // Start recording the new display list.
    glNewList(listHandleDisp, GL_COMPILE);
    glTranslatef(0,0,-20);
    loadEnemyModel();// Render a single model
    glTranslatef(0,0,-10);
    loadBossModel();// Render a single model
    // End the recording of the current display list.
    glEndList();

    // Mounting the models

    for (int y = 1 ; y <= 2 ; y++ ) {// Y quantities of ships per spawn
        spawn(3,y,1);
        glTranslatef(-1,0.5,0);
        spawn(0,y,1);
        glTranslatef(-1.5,0.5,0);
        spawn(-3,y,1);
    }

    timer->start(60);
}

// ********************************* Handlers ****************************************

// Key handler
void GLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Escape:
        close();        // Quit on Escape
        break;
    case Qt::Key_F1:
        // Toggle fullscreen on F1
        setWindowState(windowState() ^ Qt::WindowFullScreen);
        break;
    case Qt::Key_Left:  // Left Button
        _Hdistance += 1;
        break;
    case Qt::Key_Right: // Right Button
        _Hdistance -= 1;
        break;
    case Qt::Key_Up:    // Up Button
        _Vdistance += 1;
        break;
    case Qt::Key_Down:  // Down Button
        _Vdistance -= 1;
        break;
    case Qt::Key_L:     // LIGHTING OFF / ON
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

// Mouse handler
void GLWidget::mousePressEvent(QMouseEvent *event){
    m_lastPos=event->pos();
}
// /
void GLWidget::mouseMoveEvent(QMouseEvent *event){
    int dx=event->x()-m_lastPos.x();
    int dy=event->y()-m_lastPos.y();

    m_xRot+=dx;
    m_yRot+=dy;
    update();
}

// Event handler
void GLWidget::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::WindowStateChange:
        // Hide cursor if the window is fullscreen, otherwise show it
        if (windowState() == Qt::WindowFullScreen)
            setCursor(Qt::BlankCursor);
        else
            unsetCursor();
        break;
    default:
        break;
    }
}

// ******************************** Spawn handler ************************************

void GLWidget::spawn(int h, int i, int y)
{
    int c = y;  // Height

    // Assembling each model

    for (int y = 0; y <= c ; y++ ) {
        // Stack.
        glPushMatrix();
        // Position next enemy
        glTranslatef( h , i , c );
        /*glRotatef(40, 0.0, 0.0, 1.0);
        glTranslatef( 1 , i , c );*/
        glCallList(listHandleDisp);// Call the display list which renders the model.
        glPopMatrix();// Remove current MODELVIEW Matrix from stack.
    }
}

// ****************************** Update handler ************************************

void GLWidget::update()
{
    _bulletDist -= 0.07f;
    if (_bulletDist > 360) {
        _bulletDist -= 360;
    }
}

// ****************************** Texture handler ************************************

GLuint GLWidget::loadTexture(QImage image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGBA,                       //Format OpenGL uses for image
                 image.width(), image.height(),  //Width and height
                 0,                            //The border of the image
                 GL_RGBA, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image.bits());               //The actual pixel data
    return textureId; //Returns the id of the texture
}

// ******************************* Upload handler ************************************

// Upload Model
GLuint GLWidget::loadModel() {
    glmUnitize(pmodel);
    glmFacetNormals(pmodel);
    glmVertexNormals(pmodel, 90.0);
    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}

// Upload Enemy Model
GLuint GLWidget::loadEnemyModel() {
    glmUnitize(emodel);
    glmFacetNormals(emodel);
    glmVertexNormals(pmodel, 180.0);
    glmDraw(emodel, GLM_SMOOTH | GLM_MATERIAL);
}

// Upload Boss Model
GLuint GLWidget::loadBossModel()
{
    glmUnitize(bmodel);
    glmFacetNormals(bmodel);
    glmVertexNormals(pmodel, 180.0);
    glmDraw(bmodel, GLM_SMOOTH | GLM_MATERIAL);
}

// Upload Bullet Model
GLuint GLWidget::loadBulletModel()
{
    glmUnitize(bulletmodel);
    glmFacetNormals(bulletmodel);
    glmVertexNormals(bulletmodel, 180.0);
    glmDraw(bulletmodel, GLM_SMOOTH | GLM_MATERIAL);
}

