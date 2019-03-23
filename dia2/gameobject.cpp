#include "gameobject.h"
#include "transform.h"
#include "shaperenderer.h"

GameObject::GameObject(int uid, QString nameGameObject)
{
    Transform* transform = new Transform(this);
    ShapeRenderer* renderer = new ShapeRenderer(this);
    uuid = uid;
    name = nameGameObject;

    components.push_back(transform);
    components.push_back(renderer);
}

Transform* GameObject::GetTransform()
{
    for(int i = 0; i < components.size(); i++)
    {
        if(components[i]->type== Type::ComponentTransform)
        {
            // Return transform
            return (Transform*)components[i];
        }
    }
    //
    return nullptr;
}

ShapeRenderer* GameObject::GetShapeRenderer()
{
    for(int i = 0; i < components.size(); i++)
    {
        if(components[i]->type== Type::ComponentRenderer)
        {
            // Return transform
            return (ShapeRenderer*)components[i];
        }
    }
    //
    return nullptr;
}
