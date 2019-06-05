#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QColor>

namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;
class DrawRectWindow;
class ResourceManager;
class Scene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ConnectSignalsSlots();
    ResourceManager* GetResourceManager(){return resourceManager;}

public slots:

    void OpenColorDialog();
    void ColorTest();
    void updateGameObject();
    void AddGameObject();
    void RemoveGameObject();
    void SaveScene();
    void LoadScene();
    void NewScene();
    void WindowsOp();

    // Render
    void ChangeRenderMode();
    void ShowLightScene();

    // Basic Primitive
    void AddPrimitive();

    // LightSphere
    void AddLightSphere();

public:
    bool showLightScene = true;

private:
    Ui::MainWindow *ui_main_window;

    Hierarchy *hierarchy = nullptr;
    Inspector *inspector = nullptr;
    ResourceManager *resourceManager = nullptr;
    DrawRectWindow  *drawRect = nullptr;
    Scene     *scene = nullptr;

    QColorDialog *color_dialog;
    QColor testing;
};

#endif // MAINWINDOW_H
