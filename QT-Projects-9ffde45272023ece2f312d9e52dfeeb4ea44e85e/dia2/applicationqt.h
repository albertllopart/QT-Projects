#ifndef APPLICATIONQT_H
#define APPLICATIONQT_H

#define App dynamic_cast<ApplicationQt*>qApp

#include <QApplication>

class Scene;
class MainWindow;

class ApplicationQt : public QApplication
{
public:
    ApplicationQt(int &argc, char** argv);
    ~ApplicationQt();

    void Init();

    Scene* GetScene();
    void SetScene(Scene* scene);

    MainWindow* Window();

private:

    Scene* scene = nullptr;
    MainWindow* window = nullptr;


};

#endif // APPLICATIONQT_H
