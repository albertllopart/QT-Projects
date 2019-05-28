#include "widgetlight.h"
#include "ui_widgetlight.h"
#include "light.h"
#include <QColorDialog>

WidgetLight::WidgetLight(Scene* scene, Light* light, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetLight)
{
    ui->setupUi(this);

    this->scene = scene;
    this->light = light;

    ui->LightType->addItem("Directional");
    ui->LightType->addItem(".");
    ui->LightType->setCurrentIndex((int)light->GetType());
    ui->ColorButton->setStyleSheet("background-color: " + light->GetColor().name());
    ui->SliderIntensity->setValue(light->GetIntensity());
    ui->SliderRange->setValue(light->GetRange());
    ui->IntensityValue->setText(QString::number(light->GetIntensity()));
    ui->RangeValue->setText(QString::number(light->GetRange()));

    ConnectSignalsSlots();
}

WidgetLight::~WidgetLight()
{
    delete ui;
}

void WidgetLight::ConnectSignalsSlots()
{
    connect(ui->LightType,      SIGNAL(currentIndexChanged(int)),   this, SLOT(UpdateLightType()));
    connect(ui->ColorButton,    SIGNAL(clicked()),                  this, SLOT(UpdateLightColor()));
    connect(ui->SliderIntensity,SIGNAL(valueChanged(int)),          this, SLOT(UpdateLightIntensity(int)));
    connect(ui->SliderRange,    SIGNAL(valueChanged(int)),          this, SLOT(UpdateLightRange(int)));
}

void WidgetLight::UpdateLightType()
{
    light->SetType(ui->LightType->currentIndex());
    emit InspectorUpdate();
}

void WidgetLight::UpdateLightColor()
{
    QColor color = QColorDialog::getColor(light->GetColor());

    if(color.isValid())
    {
        light->SetColor(color);
        ui->ColorButton->setStyleSheet(QString("Background-Color: %0;").arg(light->GetColor().name()));

        emit InspectorUpdate();
    }
}

void WidgetLight::UpdateLightIntensity(int value)
{
    light->SetIntensity(value);
    ui->IntensityValue->setText(QString::number(light->GetIntensity()));
    emit InspectorUpdate();
}

void WidgetLight::UpdateLightRange(int value)
{
    light->SetRange(value);
    ui->RangeValue->setText(QString::number(light->GetRange()));
    emit InspectorUpdate();
}
