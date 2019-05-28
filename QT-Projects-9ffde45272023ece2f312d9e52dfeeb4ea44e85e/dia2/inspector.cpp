#include "inspector.h"
#include "ui_inspector.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include "scene.h"
#include "widget2dtransform.h"
#include "hierarchy.h"
#include "widgetshaperenderer.h"
#include "widgetmeshrenderer.h"
#include "widgetlight.h"
#include "applicationqt.h"
#include "mainwindow.h"
#include <QDebug>

Inspector::Inspector(Scene* sceneA, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inspector)
{
    //ui->setupUi(this);
    //create widgets independently
    //Head
    //QLineEdit* entity_name = new QLineEdit("Entity Name");

    scene = sceneA;
    //Body (components)
    //Wtransform = new Widget2DTransform();
    //renderer = new WidgetShapeRenderer();

    //Bottom
    //QPushButton* add_background_renderer = new QPushButton("Add Background Renderer");

    //vertical layout
    //QVBoxLayout* layout = new QVBoxLayout;

    //elements to layout
    //layout->addWidget(entity_name);
    //layout->addWidget(transform);
    //layout->addWidget(renderer);
    //layout->addWidget(add_background_renderer);

    //set the layout for this widget
    //this->setLayout(layout);
    //connect(ui->AddMeshRenderer, SIGNAL(clicked()), this, SLOT(AddMeshRenderer()));
    //connect(ui->AddMaterial, SIGNAL(clicked()), this, SLOT(AddMaterial()));

    //QPushButton* meshButton = new QPushButton();
    //meshButton->
    //connect(ui->AddMeshRenderer, SIGNAL(clicked()), this, SLOT(AddMeshRenderer()));
    //connect(ui->AddMaterial, SIGNAL(clicked()), this, SLOT(AddMaterial()));
}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::AddMeshRenderer()
{
    if (selected != nullptr)
    {
        qInfo() << "Add Mesh Renderer";
        selected->AddMeshRenderer();
        App->GetScene()->GameObjectHierarchyClicked(selected);
        emit MainUpdate();
    }
}

void Inspector::AddLight()
{
    if (selected != nullptr)
    {
        selected->AddLight();
        App->GetScene()->GameObjectHierarchyClicked(selected);
        emit MainUpdate();
    }
}

void Inspector::ShowGameObject(GameObject* selectedGO)
{
    DeleteLayout();
    selected = selectedGO;
    layout = new QVBoxLayout();

    //QWidget* widget = new QWidget();
    //connect(widget,SIGNAL(InspectorUpdate()),this,SIGNAL(MainUpdate()));

    QLineEdit* entity_name = new QLineEdit(selected->name);
    layout->addWidget(entity_name);

    qInfo() << "Nº Components" << selected->components.size();
    for(int i =0;i<selected->components.size();i++)
    {
        Component* component = selected->components[i];
        qInfo() << "Comp: " << component->name;
        layout->addWidget(GetWidget(component));
    }

    if(selected->GetMeshRenderer() == nullptr)
    {
        QPushButton* meshButton = new QPushButton("Add Mesh Renderer");
        layout->addWidget(meshButton);
        connect(meshButton, SIGNAL(clicked()), this, SLOT(AddMeshRenderer()));
    }
    if (selected->GetLight() == nullptr)
    {
        QPushButton* lightButton = new QPushButton("Add Light");
        layout->addWidget(lightButton);
        connect(lightButton, SIGNAL(clicked()), this, SLOT(AddLight()));
    }

    connect(entity_name, SIGNAL(textChanged(QString)), this, SLOT(SetName(QString)));

    setLayout(layout);

}

void Inspector::DeleteLayout()
{
    if (layout == nullptr)
        return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0)))
    {
        if(item->widget() != nullptr)
            delete item->widget();
        delete item;
    }
    delete layout;
    layout = nullptr;
}

QWidget* Inspector::GetWidget(Component* component)
{
    switch (component->type)
    {
    case Type::ComponentTransform:
    {
        Widget2DTransform* widget= new Widget2DTransform((Transform*)component);
        connect(widget,SIGNAL(InspectorUpdate()),this,SIGNAL(MainUpdate()));
        return widget;
    }
    case Type::ComponentRenderer:
    {
        WidgetShapeRenderer* widget= new WidgetShapeRenderer((ShapeRenderer*)component);
        connect(widget,SIGNAL(InspectorUpdate()),this,SIGNAL(MainUpdate()));
        return widget;
    }
    case Type::ComponentMeshRenderer:
    {
        WidgetMeshRenderer* widget = new WidgetMeshRenderer(scene, (MeshRenderer*)component);
        connect(widget, SIGNAL(InspectorUpdate()), this, SIGNAL(MainUpdate()));
        return widget;
    }
    case Type::ComponentLight:
    {
        WidgetLight* widget = new WidgetLight(scene, (Light*)component);
        connect(widget, SIGNAL(InspectorUpdate()), this, SIGNAL(MainUpdate()));
        return widget;
    }
    default:
        break;
    }

    return nullptr;
}

void Inspector::SetName(QString name)
{
    if(selected->name == name)
        return;
    selected->name = name;
    scene->hierarchy->Update();
    //emit ShowGameObject(selected);
}
