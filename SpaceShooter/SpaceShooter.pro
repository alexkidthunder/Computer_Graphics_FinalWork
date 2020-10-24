QT += core gui opengl \
    widgets

TARGET = SpaceShooter

TEMPLATE = app

SOURCES +=  \
            glm.c \
            main.cpp \
            glwidget.cpp

HEADERS +=  \
            glm.h \
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
