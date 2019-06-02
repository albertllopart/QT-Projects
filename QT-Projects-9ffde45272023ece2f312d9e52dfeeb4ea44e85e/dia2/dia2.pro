#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T10:16:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dia2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    camera.cpp \
    deferredrenderer.cpp \
    input.cpp \
        main.cpp \
        mainwindow.cpp \
    inspector.cpp \
    myopenglwidget.cpp \
    hierarchy.cpp \
    widget2dtransform.cpp \
    scene.cpp \
    gameobject.cpp \
    component.cpp \
    transform.cpp \
    widgetshaperenderer.cpp \
    drawrectwindow.cpp \
    shaperenderer.cpp \
    mesh.cpp \
    resourcemanager.cpp \
    submesh.cpp \
    meshrenderer.cpp \
    material.cpp \
    light.cpp \
    widgetmeshrenderer.cpp \
    applicationqt.cpp \
    widgetlight.cpp \
    texture.cpp

HEADERS += \
    camera.h \
    deferredrenderer.h \
    input.h \
        mainwindow.h \
    inspector.h \
    myopenglwidget.h \
    hierarchy.h \
    widget2dtransform.h \
    scene.h \
    gameobject.h \
    component.h \
    transform.h \
    widgetshaperenderer.h \
    drawrectwindow.h \
    shaperenderer.h \
    mesh.h \
    resourcemanager.h \
    submesh.h \
    meshrenderer.h \
    material.h \
    light.h \
    widgetmeshrenderer.h \
    applicationqt.h \
    widgetlight.h \
    texture.h

FORMS += \
        mainwindow.ui \
    inspector.ui \
    hierarchy.ui \
    widget2dtransform.ui \
    widgetshaperenderer.ui \
    drawrectwindow.ui \
    widgetmeshrenderer.ui \
    widgetlight.ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    shaders/LightShader.frag \
    shaders/LightShader.vert \
    shaders/GeometryShader.frag \
    shaders/GeometryShader.vert

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Assimp/lib/ -lassimpd
else:unix: LIBS += -L$$PWD/Assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/Assimp/include
DEPENDPATH += $$PWD/Assimp/include
