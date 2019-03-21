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
class drawRect;
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

private:
    Ui::MainWindow *ui_main_window;

    Hierarchy *hierarchy;
    Inspector *inspector;
    drawRect  *drawrect;
    Scene     *scene;

    QColorDialog *color_dialog;
    QColor testing;
};

#endif // MAINWINDOW_H
