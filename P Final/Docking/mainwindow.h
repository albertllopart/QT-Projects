#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
class Rendering;
}

class Inspector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;

public slots:

    void openProject();
    void saveProject();

private:
    Ui::MainWindow *uiMainWindow;
    Ui::Rendering *uiRendering;
    Inspector *inspector;
    int wits = 10;
};

#endif // MAINWINDOW_H
