#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"

enum LightType
{
    Directional = 0
};

class Light : public Component
{
public:
    Light(GameObject* gameobject);

    void Draw();

    void SetType(int type);
    void SetColor();
    void SetIntensity(int intensity);
    void SetRadius(int raius);



private:

    LightType type = LightType::Directional;
    int intensity = 10;
    int radius = 0.0f;
};

#endif // LIGHT_H
