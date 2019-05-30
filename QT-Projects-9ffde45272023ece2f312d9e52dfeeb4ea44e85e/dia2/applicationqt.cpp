#include "applicationqt.h"
#include "mainwindow.h"
#include "deferredrenderer.h"
#include "myopenglwidget.h"

ApplicationQt::ApplicationQt(int &argc, char** argv) : QApplication(argc, argv)
{

}

ApplicationQt::~ApplicationQt()
{
    //delete scene;
}

void ApplicationQt::Init()
{
    window = new MainWindow();
    window->show();
}

Scene* ApplicationQt::GetScene()
{
    return scene;
}

void ApplicationQt::SetScene(Scene* scene)
{
    this->scene = scene;
}

DeferredRenderer* ApplicationQt::GetDeferredRenderer()
{
    return deferredRenderer;
}

MyOpenGLWidget* ApplicationQt::GetMyOpenGLWidget()
{
    return myOpenGLWidget;
}

void ApplicationQt::SetMyOpenGLWidget(MyOpenGLWidget* widget)
{
    this->myOpenGLWidget = widget;
}

MainWindow* ApplicationQt::Window()
{
    return window;
}
