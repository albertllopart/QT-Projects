#include "texture.h"
#include <QOpenGLFunctions>
#include <QImage>
#include <QOpenGLTexture>
#include "myopenglwidget.h"

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
    if (texture != nullptr)
    {
        delete texture;
    }
    texture = new QOpenGLTexture(QImage(path.c_str()));
}

void Texture::Draw()
{
    if (texture != nullptr)
    {
        GL->glBindTexture(GL_TEXTURE_2D, texture->textureId());
    }
}

void Texture::UnBind()
{
    if (texture != nullptr)
    {
        GL->glBindTexture(GL_TEXTURE_2D, 0);
    }
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
    return texture->textureId();
}

TextureType Texture::GetTextureType()
{
    return type;
}



