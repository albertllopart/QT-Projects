#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QList>
#include "component.h"
#include <QJsonObject>

class Transform;
class ShapeRenderer;
class MeshRenderer;
class Light;

class GameObject
{
public:
    GameObject(int uid, QString nameGameObject);


    void AddMeshRenderer();
    void AddLight();

    Transform* GetTransform();
    ShapeRenderer* GetShapeRenderer();
    MeshRenderer* GetMeshRenderer();
    Light* GetLight();


    void Save(QJsonObject &json) const;
    void Load(const QJsonObject &json);

public:
    int uuid;
    QString name;
    QList<Component*> components;

};

#endif // GAMEOBJECT_H
