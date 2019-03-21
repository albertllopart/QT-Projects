#include "inspector.h"
#include "ui_inspector.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include "scene.h"
#include "widget2dtransform.h"
#include "hierarchy.h"
#include "widgetshaperenderer.h"

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
    //transform = new Widget2DTransform();
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

}

Inspector::~Inspector()
{
    delete ui;
}

void Inspector::ShowGameObject(GameObject* selectedGO)
{
    DeleteLayout();
    selected = selectedGO;
    layout = new QVBoxLayout();

    QWidget* widget = new QWidget();

    QLineEdit* entity_name = new QLineEdit(selected->name);
    layout->addWidget(entity_name);

    Widget2DTransform *transform = new Widget2DTransform();
    layout->addWidget(transform);

    WidgetShapeRenderer *renderer = new WidgetShapeRenderer();
    layout->addWidget(renderer);

    QPushButton* add_background_renderer = new QPushButton("Add Background Renderer");
    layout->addWidget(add_background_renderer);

    connect(entity_name, SIGNAL(textChanged(QString)), this, SLOT(SetName(QString)));

    //layout->addItem(spacer);
    setLayout(layout);

}

void Inspector::DeleteLayout()
{
    if(layout==nullptr)
        return;

    // Completely delete layout and sublayouts
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;

    while ((item = layout->takeAt(0)))
    {
        if ((sublayout = item->layout()) != 0) { /* do the same for sublayout*/ }
        else if ((widget = item->widget()) != 0) { widget->hide(); delete widget; }
        else { delete item; }
    }

    // then finally
    delete layout;

    layout = nullptr;
}

void Inspector::SetName(QString name)
{
    if(selected->name == name)
        return;
    selected->name = name;
    scene->hierarchy->Update();
    //emit ShowGameObject(selected);
}
