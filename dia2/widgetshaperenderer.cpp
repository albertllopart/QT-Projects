#include "widgetshaperenderer.h"
#include "ui_widgetshaperenderer.h"
# include "shaperenderer.h"
#include <QColorDialog>

WidgetShapeRenderer::WidgetShapeRenderer(ShapeRenderer* rendererGo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetShapeRenderer)
{
    ui->setupUi(this);

    renderer = rendererGo;
    ui->comboBox_shape->addItem("Circle");
    ui->comboBox_shape->addItem("Square");
    ui->comboBox_shape->addItem("Triangle");

    ui->pushButton_fillColor->setStyleSheet("background-color: " + renderer->fillColor.name());

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
    connect(ui->pushButton_fillColor,    SIGNAL(clicked()),                this,    SLOT(UpdateFillColor()));
    connect(ui->pushButton_strokeColor,  SIGNAL(clicked()),                this,    SLOT(UpdateStrokeColor()));
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

//SLOTS
//S'encarreguen d'actualitzar els paràmetres del GO seleccionat

void WidgetShapeRenderer::UpdateFillColor()
{
    QColor color = QColorDialog::getColor(renderer->fillColor);

    if(color.isValid())
    {
        renderer->fillColor = color;
        ui->pushButton_fillColor->setStyleSheet(QString("Background-Color: %0;").arg(renderer->fillColor.name()));

        emit InspectorUpdate();
    }
}

void WidgetShapeRenderer::UpdateStrokeColor()
{
    QColor color = QColorDialog::getColor(renderer->strokeColor);

    if(color.isValid())
    {
        renderer->strokeColor = color;
        ui->pushButton_strokeColor->setStyleSheet(QString("Background-Color: %0;").arg(renderer->strokeColor.name()));

        emit InspectorUpdate();
    }
}

void WidgetShapeRenderer::UpdateShape()
{
    switch(ui->comboBox_shape->currentIndex())
    {
        case Circle:
        {
            renderer->type = Circle;
            break;
        }
        case Square:
        {
            renderer->type = Square;
            break;
        }
        case Triangle:
        {
            renderer->type = Triangle;
            break;
        }
    }

    emit InspectorUpdate();
}

void WidgetShapeRenderer::UpdateSize()
{
    renderer->size = ui->spinBox_size->value();

    emit InspectorUpdate();
}

void WidgetShapeRenderer::UpdateStrokeThickness()
{
    renderer->strokeThickness = ui->spinBox_strokeThickness->value();

    emit InspectorUpdate();
}

void WidgetShapeRenderer::UpdateStrokeStyle()
{
    switch(ui->comboBox_strokeStyle->currentIndex())
    {
        case SolidLine:
        {
            renderer->strokeStyle = SolidLine;
            break;
        }
        case DashLine:
        {
            renderer->strokeStyle = DashLine;
            break;
        }
        case DotLine:
        {
            renderer->strokeStyle = DotLine;
            break;
        }
        case DashDotLine:
        {
            renderer->strokeStyle = DashDotLine;
            break;
        }
        case DashDotDotLine:
        {
            renderer->strokeStyle = DashDotDotLine;
            break;
        }
        case NoStroke:
        {
            renderer->strokeStyle = NoStroke;
            break;
        }
    }

    emit InspectorUpdate();
}
