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
    position = QPointF(json["Position_X"].toInt(),json["Position_Y"].toDouble());
    rotation = QPointF(json["Rotation_X"].toDouble(),json["Rotation_Y"].toDouble());
    scale = QPointF(json["Scale_X"].toDouble(),json["Scale_Y"].toDouble());
}
