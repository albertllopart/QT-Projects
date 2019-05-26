#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int numComponents = 0;
};

class VertexFormat
{
public:

    void SetVertexAttribute(int index, int offset, int numComponents)
    {
        if(index < 3)
        {
            attributes[index].enabled = true;
            attributes[index].offset = offset;
            attributes[index].numComponents = numComponents;
            size += (numComponents * sizeof(float));
        }
    }

   VertexFormat& operator=(const VertexFormat& other)
   {
       memcpy(attributes, other.attributes, sizeof(VertexAttribute) * 3);
       size = other.size;

       return *this;
   }

    VertexAttribute attributes[3];
    int size = 0;
};

class SubMesh
{
public:
    SubMesh(VertexFormat format);
    ~SubMesh() { }

    void Draw();
    void Destroy();
    void SetInfo(uint size, uint indexSize, void* data = nullptr, void* index = nullptr);

public:
    VertexFormat vertexFormat;

private:

    uchar* dfile = nullptr;
    size_t dfileSize = 0;

    uint* index = nullptr;
    size_t indexCount = 0;

    QOpenGLVertexArrayObject vertexArray;


};

#endif // SUBMESH_H
