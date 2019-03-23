#include "transform.h"

Transform::Transform(GameObject* gameobject) : Component(gameobject, Type::ComponentTransform)
{
    name = "Transform";
    position = QPoint(0,0);
    rotation = QPoint(0,0);
    scale = QPoint(1,1);
}

Transform::~Transform()
{
}
