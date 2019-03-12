#include "inspector.h"
#include "ui_inspector.h"
#include <QVBoxLayout>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

Inspector::Inspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inspector)
{
    //create widgets independently
    //Head
    QLineEdit* entity_name = new QLineEdit("Entity Name");

    //Body (components)
    transform = new Widget2DTransform;
    renderer = new WidgetShapeRenderer;

    //Bottom
    QPushButton* add_background_renderer = new QPushButton("Add Background Renderer");

    //vertical layout
    QVBoxLayout* layout = new QVBoxLayout;

    //elements to layout
    layout->addWidget(entity_name);
    layout->addWidget(transform);
    layout->addWidget(renderer);
    layout->addWidget(add_background_renderer);

    //set the layout for this widget
    setLayout(layout);
}

Inspector::~Inspector()
{
    delete ui;
}
