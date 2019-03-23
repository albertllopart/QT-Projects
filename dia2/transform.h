#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <qvector2d.h>

class Transform : public Component
{
public:
    Transform(GameObject* gameobject);
    ~Transform();



public:
    QPointF position;
    QPointF rotation;
    QPointF scale;
};

#endif // TRANSFORM_H
