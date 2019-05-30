#ifndef MATERIAL_H
#define MATERIAL_H

#include "resourcemanager.h"
#include <vector>

class Texture;

class Material : public Resource
{
public:
    Material();

    void Update() override;
    void Draw(int index);

public:
    std::string textureName = "";
    Texture* texture = nullptr;

};

#endif // MATERIAL_H
