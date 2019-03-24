#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include "component.h"
#include <QColor>
#include <QJsonObject>

enum ShapeType
{
    Circle = 0,
    Square,
    Triangle
};

enum StrokeStyle
{
    SolidLine = 0,
    DashLine,
    DotLine,
    DashDotLine,
    DashDotDotLine,
    NoStroke
};

class ShapeRenderer : public Component
{
public:

    ShapeRenderer(GameObject* gameobject);
    void Save(QJsonObject &json) const override;

public:
    ShapeType type = ShapeType::Circle;
    StrokeStyle strokeStyle = StrokeStyle::SolidLine;
    QColor fillColor;
    QColor strokeColor;
    int size = 1; // Only in circle?
    int strokeThickness = 1;

};

#endif // SHAPERENDERER_H
