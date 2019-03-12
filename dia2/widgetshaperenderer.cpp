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
}

WidgetShapeRenderer::~WidgetShapeRenderer()
{
    delete ui;
}
