#include "drawrectwindow.h"
#include "ui_drawrectwindow.h"
#include <qpainter.h>

DrawRectWindow::DrawRectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawRectWindow)
{
    ui->setupUi(this);
    setAutoFillBackground(true);
}

DrawRectWindow::~DrawRectWindow()
{
    delete ui;
}

QSize DrawRectWindow::sizeHint() const
{
    return QSize(256,256);
}

QSize DrawRectWindow::minimumSizeHint() const
{
    return QSize(64,64);
}

void DrawRectWindow::setScene(Scene *scene)
{
    this->scene = scene;
}

void DrawRectWindow::paintEvent(QPaintEvent *)
{
    QColor blueColor = QColor::fromRgb(127,190,220);
    QColor whiteColor = QColor::fromRgb(255,255,255);
    QColor blackColor = QColor::fromRgb(0,0,0);

    //
    QPainter painter(this);

    QBrush brush;
    QPen pen;

    brush.setColor(blueColor);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    // Paint background
    painter.drawRect(rect());

    // Brusg/pen Confuiguration
    brush.setColor(whiteColor);
    pen.setWidth(4);
    pen.setColor(blackColor);
    pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(brush);
    painter.setPen(pen);

    foreach(GameObject* item, scene->gameobjects)
    {
        int r = 64;
        int w = r * 2;
        int h = r * 2;
        int x = rect().width() / 2 - r;
        int y = rect().height() / 2 - r;
        QRect circleRect(x, y, w, h);
        painter.drawEllipse(circleRect);
    }
}

