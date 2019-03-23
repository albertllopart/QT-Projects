#include "component.h"

Component::Component(GameObject* gameobject, Type type)
{
    this->type = type;
    this->gameobject = gameobject;
}

Component::~Component()
{

}
