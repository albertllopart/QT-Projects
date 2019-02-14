#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int counter = 0;

public slots:

    void btn_1_onClick();
    void btn_2_onClick();
    void btn_reset_onClick();

private:
    Ui::MainWindow *ui;

    QShortcut* plus;
    QShortcut* minus;
};

#endif // MAINWINDOW_H
