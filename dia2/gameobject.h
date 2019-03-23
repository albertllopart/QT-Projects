#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QList>
#include "component.h"

class Transform;
class ShapeRenderer;

class GameObject
{
public:
    GameObject(int uid, QString nameGameObject);

    Transform* GetTransform();
    ShapeRenderer* GetShapeRenderer();

public:
    int uuid;
    QString name;
    QList<Component*> components;

};

#endif // GAMEOBJECT_H
