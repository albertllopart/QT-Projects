#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QList>
#include "component.h"
#include <QJsonObject>

class Transform;
class ShapeRenderer;

class GameObject
{
public:
    GameObject(int uid, QString nameGameObject);

    Transform* GetTransform();
    ShapeRenderer* GetShapeRenderer();

    void Save(QJsonObject &json) const;
    void Load(const QJsonObject &json);

public:
    int uuid;
    QString name;
    QList<Component*> components;

};

#endif // GAMEOBJECT_H
