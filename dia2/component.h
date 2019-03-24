#ifndef COMPONENT_H
#define COMPONENT_H

#include <qstring.h>
#include <QJsonObject>


class GameObject;

enum Type
{
    ComponentTransform,
    ComponentRenderer
};

class Component
{
public:
    Component(GameObject* gameobject,Type type);
    virtual ~Component();

    virtual void Save(QJsonObject &json) const;

public:
    QString name;
    GameObject* gameobject;
    Type type;
};

#endif // COMPONENT_H
