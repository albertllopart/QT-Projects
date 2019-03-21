#include "gameobject.h"

GameObject::GameObject(int uid, QString nameGameObject)
{
    transform = new Transform();
    uuid = uid;
    name = nameGameObject;
}
