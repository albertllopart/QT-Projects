#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow)
{
    ui_main_window->setupUi(this);

    //All tab positions on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the hierarchy widget and add it to the hierarchy
    hierarchy = new Hierarchy();
    ui_main_window->dock_hierarchy->setWidget(hierarchy);

    //Create the inspector widget and add it to the inspector
    inspector = new Inspector();
    ui_main_window->dock_inspector->setWidget(inspector);

    //Connect Signals and Slots
    ConnectSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui_main_window;
}

void MainWindow::ConnectSignalsSlots()
{
    connect(ui_main_window->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::menuBar_Action_Testing()
{

}

