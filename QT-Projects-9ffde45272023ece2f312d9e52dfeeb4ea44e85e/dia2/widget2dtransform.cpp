#include "widget2dtransform.h"
#include "ui_widget2dtransform.h"
#include "transform.h"
#include <QDebug>

Widget2DTransform::Widget2DTransform(Transform* transformGo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2DTransform)
{
    ui->setupUi(this);

    if (transform == nullptr)
    {
        transform = transformGo;
        ui->doubleSpinBox_transform_translation_x->setValue(transform->position.x());
        ui->doubleSpinBox_transform_translation_y->setValue(transform->position.y());
        ui->doubleSpinBox_position_z->setValue(transform->position.z());
        ui->doubleSpinBox_transform_scale_x->setValue(transform->scale.x());
        ui->doubleSpinBox_transform_scale_y->setValue(transform->scale.y());
        ui->doubleSpinBox_scale_z->setValue(transform->scale.z());
        ui->doubleSpinBox_transform_rotation_x->setValue(transform->rotationEuler.x());
        ui->doubleSpinBox_transform_rotation_y->setValue(transform->rotationEuler.y());
        ui->doubleSpinBox_rotation_z->setValue(transform->rotationEuler.z());
        //ui->->setValue(transform->scale.y());
        //initialSize = ui->verticalSlider->value();
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

    connect(ui->doubleSpinBox_position_z,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_scale_x,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_scale_y,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_scale_z,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_rotation_x,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_rotation_y,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_rotation_z,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));
}

void Widget2DTransform::UpdateTransform()
{
    transform->position.setX(ui->doubleSpinBox_transform_translation_x->value());
    transform->position.setY(ui->doubleSpinBox_transform_translation_y->value());
    transform->position.setZ(ui->doubleSpinBox_position_z->value());

    transform->scale.setX(ui->doubleSpinBox_transform_scale_x->value());
    transform->scale.setY(ui->doubleSpinBox_transform_scale_y->value());
    transform->scale.setZ(ui->doubleSpinBox_scale_z->value());

    transform->rotationEuler.setX(ui->doubleSpinBox_transform_rotation_x->value());
    transform->rotationEuler.setY(ui->doubleSpinBox_transform_rotation_y->value());
    transform->rotationEuler.setZ(ui->doubleSpinBox_rotation_z->value());
    transform->rotation = QQuaternion::fromEulerAngles(transform->rotationEuler);

    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}









