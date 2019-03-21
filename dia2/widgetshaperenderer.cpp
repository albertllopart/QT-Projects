#include "widgetshaperenderer.h"
#include "ui_widgetshaperenderer.h"

WidgetShapeRenderer::WidgetShapeRenderer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShapeRenderer)
{
    ui->setupUi(this);
    ui->comboBox_shape->addItem("Circle");
    ui->comboBox_shape->addItem("Square");

    ui->pushButton_fillColor->setStyleSheet("background-color: green");

    ConnectSignalsSlots();
}

WidgetShapeRenderer::~WidgetShapeRenderer()
{
    delete ui;
}

void WidgetShapeRenderer::ConnectSignalsSlots()
{
    connect(ui->comboBox_shape,          SIGNAL(currentIndexChanged(int)), this,    SLOT(UpdateShape()));
    connect(ui->spinBox_size,            SIGNAL(valueChanged(int)),        this,    SLOT(UpdateSize()));
    connect(ui->pushButton_fillColor,    SIGNAL(clicked()),                this,    SLOT(OpenColorSelector()));
    connect(ui->pushButton_strokeColor,  SIGNAL(clicked()),                this,    SLOT(OpenColorSelector()));
    connect(ui->spinBox_strokeThickness, SIGNAL(valueChanged(int)),        this,    SLOT(UpdateStrokeThickness()));
    connect(ui->comboBox_strokeStyle,    SIGNAL(currentIndexChanged(int)), this,    SLOT(UpdateStrokeStyle()));
}

void WidgetShapeRenderer::AdaptWidgetToEntity()
{
    //TODO: Actualitzar els camps del widget segons el GO al ser clicat
    //aka adaptar el widget perquè mostri les dades del GO
}

void WidgetShapeRenderer::UpdateFillColor()
{

}

void WidgetShapeRenderer::UpdateStrokeColor()
{

}

//SLOTS
//S'encarreguen d'actualitzar els paràmetres del GO seleccionat

void WidgetShapeRenderer::UpdateShape()
{

}

void WidgetShapeRenderer::UpdateSize()
{

}

void WidgetShapeRenderer::UpdateStrokeThickness()
{

}

void WidgetShapeRenderer::UpdateStrokeStyle()
{

}

void WidgetShapeRenderer::OpenColorSelector()
{

}
