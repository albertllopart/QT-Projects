#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_Rendering.h"
#include "inspector.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow),
    uiRendering(new Ui::Rendering)
{
    // Initial
    uiMainWindow->setupUi(this);
    uiMainWindow->hierarchyDock->setMinimumSize(200, 100);
    uiMainWindow->ProjectDock->setMinimumSize(100, 120);

    //Create The Inspector

    QWidget *renderingWidget = new QWidget();
    uiRendering->setupUi(renderingWidget);
    renderingWidget->show();

    inspector = new Inspector();
    uiMainWindow->InspectorDock->setWidget(inspector);
    uiMainWindow->InspectorDock->setMinimumSize(260, 100);


    uiMainWindow->RenderingDock->setWidget(renderingWidget);

    uiMainWindow->RenderingDock->setFloating(false);
    QDockWidget *lighting = new QDockWidget;
    lighting->setWindowTitle("Lighting");
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, lighting);
    tabifyDockWidget(uiMainWindow->RenderingDock, lighting);
    tabifyDockWidget(uiMainWindow->RenderingDock, uiMainWindow->InspectorDock);

    QDockWidget *toolbar = new QDockWidget;
    toolbar->setTitleBarWidget(new QWidget());
    toolbar->setMinimumSize(260, 20);
    QHBoxLayout* layout = new QHBoxLayout();
    toolbar->setLayout(layout);
    layout->addWidget(new QPushButton());
    //layout->widget()->setMinimumSize(20,20);
    this->addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, toolbar);

    connect(uiMainWindow->actionOpen_project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   // Your code here.
   this->uiMainWindow->openGLWidget->setMinimumSize(wits, 200);
   wits++;
}

void MainWindow::openProject()
{
    std::cout << "Open project" << std::endl;
}

void MainWindow::saveProject()
{
    std::cout << "Save project" << std::endl;
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
}
