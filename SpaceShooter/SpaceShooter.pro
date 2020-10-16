QT += opengl

TARGET = SpaceShooter
TEMPLATE = app
SOURCES +=  \
            bullet.cpp \
            main.cpp \
            glwidget.cpp
HEADERS +=  \
            bullet.h \
            glwidget.h
RESOURCES +=

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
