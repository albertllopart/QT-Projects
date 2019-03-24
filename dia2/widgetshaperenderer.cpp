#include "widgetshaperenderer.h"
#include "ui_widgetshaperenderer.h"
# include "shaperenderer.h"

WidgetShapeRenderer::WidgetShapeRenderer(ShapeRenderer* rendererGo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShapeRenderer)
{
    ui->setupUi(this);

    renderer = rendererGo;
    ui->comboBox_shape->addItem("Circle");
    ui->comboBox_shape->addItem("Square");
    ui->comboBox_shape->addItem("Triangle");

    ui->pushButton_fillColor->setStyleSheet("background-color: green");

    ui->comboBox_strokeStyle->addItem("Solid Line");
    ui->comboBox_strokeStyle->addItem("Dash Line");
    ui->comboBox_strokeStyle->addItem("Dot Line");
    ui->comboBox_strokeStyle->addItem("Dash Dot Line");
    ui->comboBox_strokeStyle->addItem("Dash Dot Dot Line");
    ui->comboBox_strokeStyle->addItem("No Stroke");

    ConnectSignalsSlots();
    AdaptWidgetToEntity();
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
    switch(renderer->type)
    {
        case Circle:
        {
            ui->comboBox_shape->setCurrentIndex(0);
            break;
        }
        case Square:
        {
            ui->comboBox_shape->setCurrentIndex(1);
            break;
        }
        case Triangle:
        {
            ui->comboBox_shape->setCurrentIndex(2);
            break;
        }
    }

    ui->spinBox_size->setValue(renderer->size);
    ui->spinBox_strokeThickness->setValue(renderer->strokeThickness);

    switch(renderer->strokeStyle)
    {
        case SolidLine:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(0);
            break;
        }
        case DashLine:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(1);
            break;
        }
        case DotLine:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(2);
            break;
        }
        case DashDotLine:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(3);
            break;
        }
        case DashDotDotLine:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(4);
            break;
        }
        case NoStroke:
        {
            ui->comboBox_strokeStyle->setCurrentIndex(5);
            break;
        }
    }
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
    switch(ui->comboBox_shape->currentIndex())
    {
        case Circle:
        {
            break;
        }
        case Square:
        {
            ui->comboBox_shape->setCurrentIndex(1);
            break;
        }
        case Triangle:
        {
            ui->comboBox_shape->setCurrentIndex(2);
            break;
        }
    }
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
