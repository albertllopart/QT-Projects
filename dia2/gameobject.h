#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.h"

class GameObject
{
public:
    GameObject(int uid, QString nameGameObject);
    ~GameObject();

public:
    Transform *transform = nullptr;
    int uuid;
    QString name;
};

#endif // GAMEOBJECT_H
