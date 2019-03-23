#ifndef COMPONENT_H
#define COMPONENT_H

#include <qstring.h>

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
    ~Component();

public:
    QString name;
    GameObject* gameobject;
    Type type;
};

#endif // COMPONENT_H
