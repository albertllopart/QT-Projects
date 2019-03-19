#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "inspector.h"
#include "drawrect.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow)
{
    ui_main_window->setupUi(this);
    setMinimumSize(QSize(900, 600));
    //All tab positions on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    //Create the hierarchy widget and add it to the hierarchy
    hierarchy = new Hierarchy();
    ui_main_window->dock_hierarchy->setWidget(hierarchy);

    //Create the inspector widget and add it to the inspector
    inspector = new Inspector();
    ui_main_window->dock_inspector->setWidget(inspector);

    //
    //drawrect = new drawRect();
    //ui_main_window->centralWidget->setLayout(new QVBoxLayout);
    //ui_main_window->centralWidget->layout()->addWidget(drawrect);

    //Create the color dialog
    color_dialog = new QColorDialog(this);

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
    connect(ui_main_window->actionNew_Entity, SIGNAL(triggered()), this, SLOT(OpenColorDialog()));

    connect(color_dialog, SIGNAL(color_dialog->colorSelected(testing)), this, SLOT(ColorTest()));
}

void MainWindow::OpenColorDialog()
{
    color_dialog->open();
}

void MainWindow::ColorTest()
{

}

