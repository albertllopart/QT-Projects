#include "transform.h"

Transform::Transform(GameObject* gameobject) : Component(gameobject, Type::ComponentTransform)
{
    name = "Transform";
    position = QPoint(0,0);
    rotation = QPoint(0,0);
    scale = QPoint(1,1);
}

void Transform::Save(QJsonObject &json) const
{
    json["Position_X"] = this->position.x();
    json["Position_Y"] = this->position.y();

    json["Rotation_X"] = this->rotation.x();
    json["Rotation_Y"] = this->rotation.y();

    json["Scale_X"] = this->scale.x();
    json["Scale_Y"] = this->scale.y();
}

void Transform::Load(const QJsonObject &json)
{
    position = QPoint(json["Position_X"].toInt(),json["Position_Y"].toInt());
    rotation = QPoint(json["Rotation_X"].toInt(),json["Rotation_Y"].toInt());
    scale = QPoint(json["Scale_X"].toInt(),json["Scale_Y"].toInt());
}
