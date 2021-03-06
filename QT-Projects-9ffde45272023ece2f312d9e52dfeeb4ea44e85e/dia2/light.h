#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"
#include <QColor>

enum LightType
{
    Directional = 0,
    Point = 1
};

class Light : public Component
{
public:
    Light(GameObject* gameobject);

    void Draw();

    void SetType(int type);
    void SetIntensity(int intensity);
    void SetRange(int range);

    void Save(QJsonObject &json) const override;
    void Load(const QJsonObject &json) override;

public:
    QColor GetColor();
    void SetColor(QColor color);
    int GetIntensity();
    int GetRange();
    LightType GetType();


private:

    LightType type = LightType::Directional;
    int intensity = 10;
    int range = 0.0f;
    QColor color;
};

#endif // LIGHT_H
