#include "widget2dtransform.h"
#include "ui_widget2dtransform.h"
#include "transform.h"
#include <QDebug>

Widget2DTransform::Widget2DTransform(Transform* transformGo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget2DTransform)
{
    ui->setupUi(this);

    if(transform==nullptr)
    {
        transform = transformGo;
        ui->doubleSpinBox_transform_translation_x->setValue(transform->position.x());
        ui->doubleSpinBox_transform_translation_y->setValue(transform->position.y());
        ui->doubleSpinBox_transform_scale_x->setValue(transform->scale.x());
        ui->doubleSpinBox_transform_scale_y->setValue(transform->scale.y());
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

    connect(ui->doubleSpinBox_transform_scale_x,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->doubleSpinBox_transform_scale_y,
            SIGNAL(valueChanged(double)), this, SLOT(UpdateTransform()));

    connect(ui->horizontalSliderPosition, SIGNAL(valueChanged(int)), this, SLOT(UpdateTransformSliderXPosition(int)));
    connect(ui->verticalSliderPosition, SIGNAL(valueChanged(int)), this, SLOT(UpdateTransformSliderYPosition(int)));
    connect(ui->horizontalSliderScale, SIGNAL(valueChanged(int)), this, SLOT(UpdateTransformSliderXScale(int)));
    connect(ui->verticalSliderScale, SIGNAL(valueChanged(int)), this, SLOT(UpdateTransformSliderYScale(int)));
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

void Widget2DTransform::UpdateTransformSliderXPosition(int value)
{
    int move = transform->position.x() + value - initialSize;
    //if(move < 0)
    //    move = 0;
    transform->position.setX(move);
    ui->horizontalSliderPosition->setValue(initialSize);
    ui->doubleSpinBox_transform_translation_x->setValue(transform->position.x());
    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}

void Widget2DTransform::UpdateTransformSliderYPosition(int value)
{
    int move = transform->position.y() - (value - initialSize);
    //if(move < 0)
    //    move = 0;
    transform->position.setY(move);
    ui->verticalSliderPosition->setValue(initialSize);
    ui->doubleSpinBox_transform_translation_y->setValue(transform->position.y());
    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}

void Widget2DTransform::UpdateTransformSliderXScale(int value)
{
    float temp = value - initialSize;
    float move = transform->scale.x() + (temp / 10);
    //if(move < 0)
    //    move = 0;
    transform->scale.setX(move);
    ui->horizontalSliderScale->setValue(initialSize);
    ui->doubleSpinBox_transform_scale_x->setValue(transform->scale.x());
    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}

void Widget2DTransform::UpdateTransformSliderYScale(int value)
{
    float temp = value - initialSize;
    float move = transform->scale.y() + (temp / 10);
    //if(move < 0)
    //    move = 0;
    transform->scale.setY(-move);
    ui->verticalSliderScale->setValue(initialSize);
    ui->doubleSpinBox_transform_scale_y->setValue(transform->scale.y());
    //TODO: Actualitzar transform del GO seleccionat
    emit InspectorUpdate();
}










