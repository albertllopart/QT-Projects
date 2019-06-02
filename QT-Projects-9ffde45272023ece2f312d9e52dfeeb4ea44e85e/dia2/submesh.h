#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "myopenglwidget.h"

//class Texture;
class Material;
class QOpenGLTexture;

#define MAX_VERTEX_ATTRIBUTES 3

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int numComponents = 0;
};

class VertexFormat
{
public:

    void SetVertexAttribute(int location, int offset, int numComponents)
    {
        if(location < MAX_VERTEX_ATTRIBUTES)
        {
            attribute[location].enabled = true;
            attribute[location].offset = offset;
            attribute[location].numComponents = numComponents;
            size += (numComponents * sizeof(float));
        }
    }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

class SubMesh
{
public:
    SubMesh(VertexFormat vertexFormat, void *data, int size);
    SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices, int indicesCount);

    ~SubMesh() { }

    void Draw();
    void Update();
    void Destroy();
public:
    VertexFormat vertexFormat;
    std::string textureName = "";
    std::string meshName = "";
    Material* material = nullptr;
    //Texture* texture = nullptr;
    QOpenGLTexture* texture = nullptr;

private:

    unsigned char* data = nullptr;
    size_t dataSize = 0;

    unsigned int* indice = nullptr;
    size_t indicesCount = 0;

    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    QOpenGLVertexArrayObject vao;


};

#endif // SUBMESH_H
