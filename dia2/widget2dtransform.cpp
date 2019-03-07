#include "widget2dtransform.h"
#include "ui_widget2dtransform.h"

Widget2DTransform::Widget2DTransform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2DTransform)
{
    ui->setupUi(this);
}

Widget2DTransform::~Widget2DTransform()
{
    delete ui;
}
