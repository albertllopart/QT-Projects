#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ConnectSignalsSlots();

public slots:

    void menuBar_Action_Testing();

private:
    Ui::MainWindow *ui_main_window;

    Hierarchy *hierarchy;
    Inspector *inspector;
};

#endif // MAINWINDOW_H