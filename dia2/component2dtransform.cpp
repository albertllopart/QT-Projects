#include "component2dtransform.h"
#include "ui_component2dtransform.h"

Component2DTransform::Component2DTransform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Component2DTransform)
{
    ui->setupUi(this);
}

Component2DTransform::~Component2DTransform()
{
    delete ui;
}
