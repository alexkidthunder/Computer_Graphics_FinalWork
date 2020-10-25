QT += opengl \
    widgets \
    multimedia

TARGET = NewSpaceShooter

TEMPLATE = app

SOURCES +=  main.cpp \
            bullet.cpp \
            enemy.cpp \
            game.cpp \
            glm.c \
            glwidget.cpp \
            health.cpp \
            player.cpp \
            score.cpp

HEADERS +=  glwidget.h \
            bullet.h \
            enemy.h \
            game.h \
            health.h \
            materials.h \
            glm.h \
            player.h \
            score.h

RESOURCES += res.qrc

win32 {
    INCLUDEPATH +=


    LIBS += \
        -lopengl32 \
        -lglu32
}

unix {
    INCLUDEPATH += /usr/include

    LIBS += \
        -lGL \
        -lGLU
}

DISTFILES +=



