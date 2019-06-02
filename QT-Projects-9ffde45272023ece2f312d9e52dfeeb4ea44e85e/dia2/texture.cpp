#include "texture.h"
#include <QOpenGLFunctions>
#include <QImage>
#include <QOpenGLTexture>

Texture::Texture() : Resource(RTexture)
{

}

Texture::~Texture()
{

}

void Texture::Update()
{

}

void Texture::Load()
{

}

void Texture::Draw()
{

}

void Texture::Destroy()
{

}

void Texture::SetType(TextureType type)
{
    this->type = type;
}

void Texture::SetPath(std::string path)
{
    this->path = path;
}

unsigned int Texture::GetIndex()
{
    return id;
}

TextureType Texture::GetTextureType()
{
    return type;
}



