#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"

class GameObject
{
public:
    GameObject();

public:
    Transform *transform = nullptr;
};

#endif // GAMEOBJECT_H
