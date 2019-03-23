#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include "component.h"
#include <QColor>

enum ShapeType
{
    Circle = 0,
    Square,
    Triangle
};

class ShapeRenderer : public Component
{
public:
    ShapeRenderer(GameObject* gameobject);
    ~ShapeRenderer();

public:
    ShapeType type = ShapeType::Circle;
    QColor fillColor;
    QColor strokeColor;
    int size; // Only in circle?

};

#endif // SHAPERENDERER_H
