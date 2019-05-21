#include "component.h"

Component::Component(GameObject* gameobject, Type type)
{
    this->type = type;
    this->gameobject = gameobject;
}

Component::~Component()
{

}

void Component::Save(QJsonObject &json) const
{

}
void Component::Load(const QJsonObject &json)
{

}
