#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourcemanager.h"

enum TextureType
{
    Albedo = 0,
    Normal
};

class Texture : public Resource
{
public:
    Texture();
    ~Texture() override;

    void Update() override;
    void Draw() override;
    void Destroy() override;

    void Load();

    void SetType(TextureType type);
    void SetPath(std::string path);
    uint GetIndex();
    TextureType GetTextureType();

private:

    uint id = 0;
    TextureType type = TextureType::Albedo;
    std::string path = "";


};

#endif // TEXTURE_H
