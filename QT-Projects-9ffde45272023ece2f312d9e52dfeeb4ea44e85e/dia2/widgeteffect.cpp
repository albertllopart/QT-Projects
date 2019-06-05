#include "widgeteffect.h"
#include "ui_widgeteffect.h"
#include <QColorDialog>
#include "applicationqt.h"
#include "mainwindow.h"
#include "deferredrenderer.h"
#include "myopenglwidget.h"


WidgetEffect::WidgetEffect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetEffect)
{
    ui->setupUi(this);

    ConnectSignalsSlots();
}

WidgetEffect::~WidgetEffect()
{
    delete ui;
}

void WidgetEffect::ConnectSignalsSlots()
{
    connect(ui->colorLight,     SIGNAL(clicked()),                this, SLOT(UpdateLightSceneColor()));
    connect(ui->inputIntensity, SIGNAL(valueChanged(int)),        this, SLOT(UpdateLightSceneIntensity(int)));
    connect(ui->inputRange,     SIGNAL(valueChanged(int)),        this, SLOT(UpdateLightSceneRange(int)));

    connect(ui->comboEffect, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(UpdateEffect(const QString&)));
    connect(ui->blurIntensity, SIGNAL(valueChanged(double)), this, SLOT(UpdateIntensityBlur()));
    connect(ui->bloomAccept, SIGNAL(valueChanged(double)), this, SLOT(UpdateAcceptBloom()));
}

void WidgetEffect::UpdateValues()
{
    QColor temp = QColor(App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Color.x(),
                         App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Color.y(),
                         App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Color.z(), 1.0);

    if(temp.isValid())
    {
        ui->colorLight->setStyleSheet(QString("Background-Color: %0;").arg(temp.name()));
    }
    ui->inputIntensityNumber->setText(QString::number(App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Intensity));
    int valueI = App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Intensity;
    ui->inputIntensity->setValue(valueI);
    ui->inputRangeNumber->setText(QString::number(App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Intensity));
    valueI = App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Radius;
    ui->inputRange->setValue(valueI);
}

void WidgetEffect::UpdateLightSceneColor()
{

    QColor temp = QColor("#070606");
    QColor color = QColorDialog::getColor(temp);

    if(color.isValid())
    {
        App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Color = QVector3D(color.red(), color.green(), color.blue());
        ui->colorLight->setStyleSheet(QString("Background-Color: %0;").arg(color.name()));
        App->Window()->updateGameObject();
    }
}

void WidgetEffect::UpdateLightSceneIntensity(int value)
{
    float valueF = value;
    App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Intensity = valueF / 10.0f;
    ui->inputIntensityNumber->setText(QString::number(valueF / 10.0f));
    App->Window()->updateGameObject();
}

void WidgetEffect::UpdateLightSceneRange(int value)
{
    App->GetMyOpenGLWidget()->deferredRenderer->sceneLightInit.Radius = value;
    ui->inputRangeNumber->setText(QString::number(value));
    App->Window()->updateGameObject();
}


void WidgetEffect::UpdateEffect(const QString& nameSubmesh)
{
    if (nameSubmesh == "Deferred")
    {
        App->Window()->showEffect = 0;
    }
    else if (nameSubmesh == "Blur")
    {
        App->Window()->showEffect = 1;
    }
    else if (nameSubmesh == "Bloom")
    {
        App->Window()->showEffect = 2;
    }
    App->Window()->updateGameObject();
}

void WidgetEffect::UpdateIntensityBlur()
{
    App->GetMyOpenGLWidget()->deferredRenderer->intensityBlur = ui->blurIntensity->value();
    App->Window()->updateGameObject();
}

void WidgetEffect::UpdateAcceptBloom()
{
    App->GetMyOpenGLWidget()->deferredRenderer->acceptBloom = ui->bloomAccept->value();
    App->Window()->updateGameObject();
}






