#include "transform.h"

Transform::Transform(GameObject* gameobject) : Component(gameobject, Type::ComponentTransform)
{
    name = "Transform";
    position = QVector3D(0,0,0);
    rotationEuler = QVector3D(0,0,0);
    rotation = QQuaternion::fromEulerAngles(rotationEuler);
    scale = QVector3D(1,1,1);
}

void Transform::Save(QJsonObject &json) const
{
    json["Position_X"] = this->position.x();
    json["Position_Y"] = this->position.y();
    json["Position_Z"] = this->position.z();

    json["Rotation_X"] = this->rotation.x();
    json["Rotation_Y"] = this->rotation.y();
    json["Rotation_Z"] = this->rotation.z();

    json["Scale_X"] = this->scale.x();
    json["Scale_Y"] = this->scale.y();
    json["Scale_Z"] = this->scale.z();
}

void Transform::Load(const QJsonObject &json)
{
    position = QVector3D(json["Position_X"].toInt(),
            json["Position_Y"].toDouble(), json["Position_Z"].toDouble());
    rotationEuler = QVector3D(json["Rotation_X"].toDouble(),
            json["Rotation_Y"].toDouble(), json["Rotation_Z"].toDouble());
    rotation = QQuaternion::fromEulerAngles(rotationEuler);
    scale = QVector3D(json["Scale_X"].toDouble(),
            json["Scale_Y"].toDouble(), json["Scale_Z"].toDouble());
}

QMatrix4x4 Transform::GetTransformMatrix()
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();

    matrix.translate(position.x(), position.y(), position.z());
    matrix.rotate(rotation);
    matrix.scale(scale.x(), scale.y(), scale.z());

    return matrix;
}
