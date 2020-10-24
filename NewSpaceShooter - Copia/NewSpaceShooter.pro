QT += opengl

TARGET = NewSpaceShooter

TEMPLATE = app

SOURCES +=  main.cpp \
            glm.c \
            glwidget.cpp

HEADERS +=  glwidget.h \
            materials.h \
            glm.h

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



