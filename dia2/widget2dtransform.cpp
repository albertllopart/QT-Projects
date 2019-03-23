#include "widget2dtransform.h"
#include "ui_widget2dtransform.h"
#include "transform.h"

Widget2DTransform::Widget2DTransform(Transform* transformGo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2DTransform)
{
    ui->setupUi(this);

    if(transform!=nullptr)
    {
        transform = transformGo;
        ui->doubleSpinBox_transform_translation_x->setValue(transform->position.x());
        ui->doubleSpinBox_transform_translation_y->setValue(transform->position.y());
    }
    ConnectSignalsSlots();
}

Widget2DTransform::~Widget2DTransform()
{
    delete ui;
}

void Widget2DTransform::ConnectSignalsSlots()
{
    connect(ui->doubleSpinBox_transform_translation_x,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_translation_y,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_scale_x,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_scale_y,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));
}

void Widget2DTransform::UpdateTransform()
{
    transform->position.setX(ui->doubleSpinBox_transform_translation_x->value());
    transform->position.setY(ui->doubleSpinBox_transform_translation_y->value());

    transform->scale.setX(ui->doubleSpinBox_transform_scale_x->value());
    transform->scale.setY(ui->doubleSpinBox_transform_scale_y->value());

    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}
