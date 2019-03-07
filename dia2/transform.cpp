#include "transform.h"

Transform::Transform() : Component()
{
    name = "Transform";
    position = new QVector2D(0.0f,0.0f);
}

Transform::~Transform()
{
}
