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

void GameObject::Save(QJsonObject &json) const
{
    json["Name"] = this->name;
    json["UUID"] = this->uuid;
    for(int i = 0; i < components.size(); i++)
    {
        QJsonObject gObject;
        QString name;
        name = "Component_" + QString::number(i);
        components.at(i)->Save(gObject);
        json[name] = gObject;
    }
}

void GameObject::Load(const QJsonObject &json)
{
    this->name = json["Name"].toString();
    this->uuid = json["UUID"].toInt();
    for(int i = 0; i < components.size(); i++)
    {
        QJsonObject gObject;
        QString name;
        name = "Component_" + QString::number(i);
        gObject = json[name].toObject();
        components.at(i)->Load(gObject);
    }
}









