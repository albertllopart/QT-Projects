#include "light.h"

Light::Light(GameObject* gameobject) : Component(gameobject, Type::ComponentLight)
{
    name = "Light";
    color = QColor(255,255,255);
}

void Light::Draw()
{

}

void Light::SetType(int type)
{
    this->type = (LightType)type;
}

void Light::SetIntensity(int intensity)
{
    this->intensity = intensity;
}

void Light::SetRange(int range)
{
    this->range = range;
}

QColor Light::GetColor()
{
    return color;
}

void Light::SetColor(QColor color)
{
    this->color = color;
}

int Light::GetIntensity()
{
    return intensity;
}

int Light::GetRange()
{
    return range;
}

LightType Light::GetType()
{
    return type;
}

void Light::Save(QJsonObject &json) const
{
    json["Type"] = (int)type;
    json["Intensity"] = intensity;
    json["Range"] = range;
    json["Color_R"] = color.red();
    json["Color_G"] = color.green();
    json["Color_B"] = color.blue();

}

void Light::Load(const QJsonObject &json)
{
    type = (LightType)json["Type"].toInt();
    intensity = json["Intensity"].toInt();
    range = json["Range"].toInt();
    color = QColor(json["Color_R"].toInt(), json["Color_G"].toInt(), json["Color_B"].toInt());
}


