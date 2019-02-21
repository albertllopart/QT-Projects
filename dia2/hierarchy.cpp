#include "hierarchy.h"
#include "ui_hierarchy.h"

Hierarchy::Hierarchy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy)
{
    ui->setupUi(this);
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
    ui->listWidget_entities->addItem("testing");
}

Hierarchy::~Hierarchy()
{
    delete ui;
}
