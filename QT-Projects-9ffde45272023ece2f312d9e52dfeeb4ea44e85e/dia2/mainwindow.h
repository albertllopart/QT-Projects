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

public slots:

    void OpenColorDialog();
    void ColorTest();
    void updateGameObject();
    void AddGameObject();
    void RemoveGameObject();
    void SaveScene();
    void LoadScene();
    void NewScene();

public:
    bool showLightScene = true;

private:
    Ui::MainWindow *ui_main_window;

    Hierarchy *hierarchy;
    Inspector *inspector;
    ResourceManager *resourceManager;
    DrawRectWindow  *drawRect;
    Scene     *scene;

    QColorDialog *color_dialog;
    QColor testing;
};

#endif // MAINWINDOW_H
