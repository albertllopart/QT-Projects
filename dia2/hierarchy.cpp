#include "hierarchy.h"
#include "ui_hierarchy.h"
#include "scene.h"
#include<QDebug>

Hierarchy::Hierarchy(Scene* sceneA, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
    scene = sceneA;

    gameobjects = new QList<int>();

    ConnectSignalsSlots();
}

Hierarchy::~Hierarchy()
{
    delete ui;
}

void Hierarchy::ConnectSignalsSlots()
{
    connect(ui->pushButton_addEntity,SIGNAL(clicked()), this, SLOT(AddGameObject()));
    connect(ui->pushButton_removeEntity,SIGNAL(clicked()), this, SLOT(RemoveGameObject()));
    connect(ui->listWidget_entities, SIGNAL(itemClicked(QListWidgetItem*)), this,
            SLOT(GameObjectClicked(QListWidgetItem*)));
}

void Hierarchy::AddGameObject()
{
    GameObject* gameobject = scene->CreateGameObject();
    gameobjects->push_back(gameobject->uuid);
    ui->listWidget_entities->addItem(gameobject->name);
}

void Hierarchy::RemoveGameObject()
{
    //ui->listWidget_entities->removeItemWidget(ui->listWidget_entities->item(1));
    QList<QListWidgetItem*> items = ui->listWidget_entities->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        scene->RemoveGameObject(gameobjects->at(ui->listWidget_entities->row(item)));
        delete ui->listWidget_entities->takeItem(ui->listWidget_entities->row(item));
    }
}

void Hierarchy::GameObjectClicked(QListWidgetItem* itemSelected)
{

    QList<QListWidgetItem*> items = ui->listWidget_entities->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        if(item == itemSelected)
        {
            qInfo() << "C++ Style Info Message";
            scene->GameObjectHierarchyClicked(gameobjects->at(ui->listWidget_entities->row(item)));

        }
    }
}

void Hierarchy::Update()
{
    ui->listWidget_entities->clear();
    for(int i=0;i<scene->gameobjects.count();i++)
    {
        GameObject* item = scene->gameobjects[i];
        ui->listWidget_entities->addItem(item->name);
    }
}


