#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "inspector.h"
#include "drawrectwindow.h"
#include "scene.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow)
{
    ui_main_window->setupUi(this);
    setMinimumSize(QSize(1200, 600));
    //All tab positions on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    scene = new Scene();

    //Create the hierarchy widget and add it to the hierarchy
    hierarchy = new Hierarchy(scene);
    ui_main_window->dock_hierarchy->setWidget(hierarchy);

    //Create the inspector widget and add it to the inspector
    inspector = new Inspector(scene);
    ui_main_window->dock_inspector->setWidget(inspector);
    ui_main_window->dock_inspector->setMinimumWidth(300);

    //
    scene->SyncWindows(inspector, hierarchy);
    //drawRect = new DrawRectWindow(scene);
    //ui_main_window->centralWidget->setLayout(new QVBoxLayout);
    //ui_main_window->centralWidget->layout()->addWidget(drawRect);
    //drawRect = ui_main_window->SceneRect;
    //drawRect->setScene(scene);
    ui_main_window->SceneRect->setScene(scene);

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

    connect(hierarchy->ui->pushButton_addEntity,SIGNAL(clicked()), this, SLOT(AddGameObject()));
    connect(hierarchy->ui->pushButton_removeEntity,SIGNAL(clicked()), this, SLOT(RemoveGameObject()));

    connect(color_dialog, SIGNAL(color_dialog->colorSelected(testing)), this, SLOT(ColorTest()));
    connect(inspector, SIGNAL(MainUpdate()), this, SLOT(updateGameObject()));

    connect(ui_main_window->actionSave_Scene, SIGNAL(clicked()), this, SLOT());
}

void MainWindow::OpenColorDialog()
{
    //color_dialog->open();
    this->setWindowTitle(QString::number(scene->gameobjects.size()));
}

void MainWindow::ColorTest()
{

}

void MainWindow::updateGameObject()
{
     //qInfo() << "C++ Style Info Message";
     ui_main_window->SceneRect->update();
}

void MainWindow::AddGameObject()
{
    GameObject* gameobject = scene->CreateGameObject();
    hierarchy->AddGameObject(gameobject);
    ui_main_window->SceneRect->update();
}

void MainWindow::RemoveGameObject()
{
    int index = hierarchy->ui->listWidget_entities->currentRow();
    if(index < 0 || index > scene->gameobjects.size())
        return; // No Remove...
    qInfo() << "1";
    inspector->DeleteLayout();
    qInfo() << "2";
    hierarchy->RemoveGameObject();
    qInfo() << "3";
        qInfo() << index;
    scene->RemoveGameObject(index);
    qInfo() << "4";
    ui_main_window->SceneRect->update();
}



