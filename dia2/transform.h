#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <qvector2d.h>

class Transform : public Component
{
public:
    Transform();
    ~Transform();

public:
    QVector2D *position;
};

#endif // TRANSFORM_H
