#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class Transform : public Component
{
public:
    Transform(GameObject* gameobject);

    void Save(QJsonObject &json) const override;
    void Load(const QJsonObject &json) override;

    QMatrix4x4 GetTransformMatrix();


public:
    QVector3D position;
    QVector3D rotationEuler;
    QQuaternion rotation;
    QVector3D scale;
};

#endif // TRANSFORM_H
