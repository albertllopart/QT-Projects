#include "applicationqt.h"
#include "mainwindow.h"

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

MainWindow* ApplicationQt::Window()
{
    return window;
}
