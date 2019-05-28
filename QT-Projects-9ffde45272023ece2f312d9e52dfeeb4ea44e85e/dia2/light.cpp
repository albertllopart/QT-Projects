#include "light.h"

Light::Light(GameObject* gameobject) : Component(gameobject, Type::ComponentLight)
{
    name = "Light";
}

void Light::Draw()
{

}

void Light::SetType(int type)
{
    this->type = (LightType)type;
}

void Light::SetColor()
{

}

void Light::SetIntensity(int intensity)
{
    this->intensity =intensity;
}

void Light::SetRadius(int raius)
{
    this->radius = radius;
}
