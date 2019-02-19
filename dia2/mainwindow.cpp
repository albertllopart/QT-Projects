#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow),
    ui_rendering(new Ui::Rendering)
{
    ui_main_window->setupUi(this);

    //All tab positions on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the rendering widget
    QWidget *renderingWidget = new QWidget();
    ui_rendering->setupUi(renderingWidget);
    renderingWidget->show();

    //Add it to rendering dock
    ui_main_window->dock_rendering->setWidget(renderingWidget);

    //tabify with inspector
    ui_main_window->dock_rendering->setFloating(false);
    tabifyDockWidget(ui_main_window->dock_inspector, ui_main_window->dock_rendering);

    //Create the inspector widget and add it to the inspector
    inspector = new Inspector();
    ui_main_window->dock_inspector->setWidget(inspector);

    //Connect Signals and Slots
    ConnectSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui_main_window;
    delete ui_rendering;
}

void MainWindow::ConnectSignalsSlots()
{
    connect(ui_main_window->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::menuBar_Action_Testing()
{

}

