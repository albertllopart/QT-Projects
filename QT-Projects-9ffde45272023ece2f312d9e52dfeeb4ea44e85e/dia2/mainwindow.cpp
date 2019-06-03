#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "inspector.h"
#include "drawrectwindow.h"
#include "scene.h"
#include "resourcemanager.h"
#include "applicationqt.h"

#include <QDebug>
#include <qjsonobject.h>
#include <QFileDialog>
#include <QJsonDocument>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_main_window(new Ui::MainWindow)
{
    ui_main_window->setupUi(this);
    setMinimumSize(QSize(1200, 660));
    //All tab positions on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    scene = new Scene();
    App->SetScene(scene);

    //Create the hierarchy widget and add it to the hierarchy
    hierarchy = new Hierarchy(scene);
    ui_main_window->dock_hierarchy->setWidget(hierarchy);

    //Create the inspector widget and add it to the inspector
    inspector = new Inspector(scene);
    ui_main_window->dock_inspector->setWidget(inspector);
    ui_main_window->dock_inspector->setMinimumWidth(300);

    //
    //drawRect = new DrawRectWindow(scene);
    //ui_main_window->centralWidget->setLayout(new QVBoxLayout);
    //ui_main_window->centralWidget->layout()->addWidget(drawRect);
    //drawRect = ui_main_window->SceneRect;
    //drawRect->setScene(scene);
    //ui_main_window->SceneRect->setScene(scene);

    qInfo() << "C++ Style Info Message";
    QDockWidget* resource_dock = new QDockWidget();
    resource_dock->setWindowTitle("Resources");
    resourceManager = new ResourceManager();
    resourceManager->ImportAssets();
    resource_dock->setWidget(resourceManager);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, resource_dock);
    tabifyDockWidget(ui_main_window->dock_inspector, resource_dock);

    scene->SyncWindows(inspector, hierarchy, resourceManager);
    //Create the color dialog
    color_dialog = new QColorDialog(this);

    //QMainWindow::showEvent(event);
    QTimer::singleShot(10, this, SLOT(WindowsOp()));

    //Connect Signals and Slots
    ConnectSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui_main_window;
}

void MainWindow::WindowsOp()
{
    resourceManager->FixedResources();
    return;
}

void MainWindow::ConnectSignalsSlots()
{
    connect(ui_main_window->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui_main_window->actionNew_Entity, SIGNAL(triggered()), this, SLOT(OpenColorDialog()));

    connect(hierarchy->ui->pushButton_addEntity,SIGNAL(clicked()), this, SLOT(AddGameObject()));
    connect(hierarchy->ui->pushButton_removeEntity,SIGNAL(clicked()), this, SLOT(RemoveGameObject()));

    connect(color_dialog, SIGNAL(color_dialog->colorSelected(testing)), this, SLOT(ColorTest()));
    connect(inspector, SIGNAL(MainUpdate()), this, SLOT(updateGameObject()));

    connect(ui_main_window->actionSave_Scene, SIGNAL(triggered()), this, SLOT(SaveScene()));
    connect(ui_main_window->actionOpen_Scene, SIGNAL(triggered()), this, SLOT(LoadScene()));
    connect(ui_main_window->actionNew_Scene, SIGNAL(triggered()), this, SLOT(NewScene()));
    connect(ui_main_window->actionactionSave_Scene_Icon, SIGNAL(triggered()), this, SLOT(SaveScene()));
    connect(ui_main_window->actionactionOpen_Scene_Icon, SIGNAL(triggered()), this, SLOT(LoadScene()));
    connect(ui_main_window->actionactionNew_Scene_Icon, SIGNAL(triggered()), this, SLOT(NewScene()));

    // Render
    connect(ui_main_window->actionDeffered, SIGNAL(triggered()), this, SLOT(ChangeRenderMode()));
    ui_main_window->actionDeffered->setObjectName(QString::number(0));
    connect(ui_main_window->actionNormal, SIGNAL(triggered()), this, SLOT(ChangeRenderMode()));
    ui_main_window->actionNormal->setObjectName(QString::number(1));
    connect(ui_main_window->actionDiffuse, SIGNAL(triggered()), this, SLOT(ChangeRenderMode()));
    ui_main_window->actionDiffuse->setObjectName(QString::number(2));
    connect(ui_main_window->actionFragg, SIGNAL(triggered()), this, SLOT(ChangeRenderMode()));
    ui_main_window->actionFragg->setObjectName(QString::number(3));
    connect(ui_main_window->actionelse, SIGNAL(triggered()), this, SLOT(ChangeRenderMode()));
    ui_main_window->actionelse->setObjectName(QString::number(4));

    connect(ui_main_window->actionLightScene, SIGNAL(triggered()), this, SLOT(ShowLightScene()));
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
    inspector->DeleteLayout();
    hierarchy->RemoveGameObject();
    scene->RemoveGameObject(index);
    ui_main_window->SceneRect->update();
}

void MainWindow::SaveScene()
{
    // Open popup to save scene
    QString path = QFileDialog::getSaveFileName(this, tr("Save Scene"), "", tr("JSon (*.json);;All Files (*)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(file.open(QIODevice::WriteOnly))
        {
            // Go to save
            QJsonObject json;
            scene->SaveScene(json);
            QJsonDocument saveDocument(json);
            file.write(saveDocument.toJson());
        }
    }
}

void MainWindow::LoadScene()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Save Scene"), "", tr("JSon (*.json);;All Files (*)"));
    if(!path.isEmpty())
    {
        QFile file(path);
        if(file.open(QIODevice::ReadOnly))
        {
            // Go to save
            NewScene();
            QByteArray loadFile = file.readAll();
            QJsonDocument loadDocument(QJsonDocument::fromJson(loadFile));
            scene->LoadScene(loadDocument.object());
        }
    }
}

void MainWindow::NewScene()
{
    inspector->DeleteLayout();
    hierarchy->RemoveAll();
    int size = scene->gameobjects.size();
    for(int i = 0; i < size; i++)
    {
        scene->RemoveGameObject(0);
    }
    ui_main_window->SceneRect->update();
}

void MainWindow::ChangeRenderMode()
{
    int index = std::stoi(sender()->objectName().toStdString());
    App->GetMyOpenGLWidget()->deferredRenderer->renderView = index;
    updateGameObject();
}

void MainWindow::ShowLightScene()
{
    showLightScene = !showLightScene;
    updateGameObject();
}













