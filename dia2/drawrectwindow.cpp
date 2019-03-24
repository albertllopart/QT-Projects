#include "drawrectwindow.h"
#include "ui_drawrectwindow.h"
#include <qpainter.h>
#include "transform.h"
#include "shaperenderer.h"
#include <QDebug>

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

        Transform* transform = item->GetTransform();
        ShapeRenderer* renderer = item->GetShapeRenderer();

        brush.setColor(renderer->fillColor);
        pen.setColor(renderer->strokeColor);
        pen.setWidth(renderer->strokeThickness);

        switch(renderer->strokeStyle)
        {
            case SolidLine:
            {
                pen.setStyle(Qt::PenStyle::SolidLine);
                break;
            }
            case DashLine:
            {
                pen.setStyle(Qt::PenStyle::DashLine);
                break;
            }
            case DotLine:
            {
                pen.setStyle(Qt::PenStyle::DotLine);
                break;
            }
            case DashDotLine:
            {
                pen.setStyle(Qt::PenStyle::DashDotLine);
                break;
            }
            case DashDotDotLine:
            {
                pen.setStyle(Qt::PenStyle::DashDotDotLine);
                break;
            }
            case NoStroke:
            {
                pen.setStyle(Qt::PenStyle::NoPen);
                break;
            }
        }

        painter.setBrush(brush);
        painter.setPen(pen);

        QRect rect(transform->position.x(), transform->position.y(), renderer->size * transform->scale.x(), renderer->size * transform->scale.y());

        switch(renderer->type)
        {
            case Circle:
            {
                painter.drawEllipse(rect);
                break;
            }
            case Square:
            {
                painter.drawRect(rect);
                break;
            }
            case Triangle:
            {
                QPolygon poly(3);
                qInfo() << QString::number(poly.count());
                //poly.
                poly.setPoint(0, rect.bottomLeft().x(), rect.bottomLeft().y());
                poly.setPoint(1, rect.bottomRight().x(), rect.bottomRight().y());
                poly.setPoint(2, QPoint(rect.left() + renderer->size, rect.top()).x(), QPoint(rect.left() + renderer->size, rect.top()).y());
                qInfo() << QString::number(poly.count());
                painter.drawPolygon(poly);
                break;
            }
        }
    }
}

