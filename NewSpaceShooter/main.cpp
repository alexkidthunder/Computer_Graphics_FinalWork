#include <QApplication>
#include "glwidget.h"
#include "game.h"

Game * game;

int main(int argc, char *argv[]) {

    // Construct a new Qt application
    QApplication a(argc, argv);

    // Check for OpenGL support
    if (!QGLFormat::hasOpenGL()) {
        qDebug("Your system does not seem to support OpenGL. Cannot run this example.");
        return EXIT_FAILURE;
    }

    // Create and show OpenGL window
    GLWidget w;
    w.setMinimumSize(800, 600);
    w.show();

    // Create and show 2D window
    game = new Game();
    game->show();

    // Let's roll!
    return a.exec();
}
