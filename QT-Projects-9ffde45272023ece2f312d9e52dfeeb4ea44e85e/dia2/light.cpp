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
    this->intensity =intensity;
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


