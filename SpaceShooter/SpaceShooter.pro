QT += opengl

TARGET = SpaceShooter

TEMPLATE = app

SOURCES +=  \
            bullet.cpp \
            enemy.cpp \
            main.cpp \
            glwidget.cpp

HEADERS +=  \
            bullet.h \
            enemy.h \
            glwidget.h

RESOURCES += \
    res.qrc

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
