#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plus = new QShortcut(QKeySequence("+"), ui->btn_1);
    minus = new QShortcut(QKeySequence("-"), ui->btn_2);

    connect(plus, SIGNAL(activated()), this, SLOT(btn_1_onClick()));
    connect(minus, SIGNAL(activated()), this, SLOT(btn_2_onClick()));

    connect(ui->btn_1, SIGNAL(clicked()), this, SLOT(btn_1_onClick()));
    connect(ui->btn_2, SIGNAL(clicked()), this, SLOT(btn_2_onClick()));
    connect(ui->btn_reset, SIGNAL(clicked()), this, SLOT(btn_reset_onClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_1_onClick()
{

    QString to_text = QString::number(++counter);
    ui->label->setText(to_text);
}

void MainWindow::btn_2_onClick()
{
    QString to_text = QString::number(--counter);
    ui->label->setText(to_text);
}

void MainWindow::btn_reset_onClick()
{
    counter = 0;
    QString to_text = QString::number(counter);
    ui->label->setText(to_text);
}
