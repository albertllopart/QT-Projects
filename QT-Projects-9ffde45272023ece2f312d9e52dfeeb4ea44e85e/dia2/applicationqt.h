#ifndef APPLICATIONQT_H
#define APPLICATIONQT_H

#define App dynamic_cast<ApplicationQt*>qApp

#include <QApplication>

class Scene;
class MainWindow;
class DeferredRenderer;
class MyOpenGLWidget;

class ApplicationQt : public QApplication
{
public:
    ApplicationQt(int &argc, char** argv);
    ~ApplicationQt();

    void Init();

    Scene* GetScene();
    void SetScene(Scene* scene);

    DeferredRenderer* GetDeferredRenderer();

    MyOpenGLWidget* GetMyOpenGLWidget();
    void SetMyOpenGLWidget(MyOpenGLWidget* widget);

    MainWindow* Window();

private:

    Scene* scene = nullptr;
    MainWindow* window = nullptr;
    DeferredRenderer* deferredRenderer = nullptr;
    MyOpenGLWidget* myOpenGLWidget = nullptr;

};

#endif // APPLICATIONQT_H
