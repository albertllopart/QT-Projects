#include "submesh.h"
#include <iostream>
#include <QOpenGLFunctions>

SubMesh::SubMesh(VertexFormat format)
{
    vertexFormat = format;
}


void SubMesh::SetInfo(uint size, uint indexSize, void *dfile, void *index)
{
    this->dfile = new uchar[size];
    memcpy(this->dfile, dfile, size);
    dfileSize = size;
    //
    this->index = new uint[indexSize];
    memcpy(this->index, index, indexSize * sizeof(uint));
    indexCount = indexSize;
}

void SubMesh::Update()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    vertexbo.create();
    vertexbo.bind();

    if(dfile != nullptr)
    {
        vertexbo.create();
        vertexbo.bind();
        vertexbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        vertexbo.allocate(dfile, int(dfileSize));
        delete[] dfile;
        dfile = nullptr;
    }

    // IBO: buffer with index
    if(indexCount > 0)
    {
        indexbo.create();
        indexbo.bind();
        indexbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        indexbo.allocate(index, int(indexCount * sizeof(unsigned int)));
        delete[] index;
        index = nullptr;
    }

    for (int i = 0; i < 3; i++)
    {
        VertexAttribute& attribute = vertexFormat.attributes[i];

        if(attribute.enabled)
        {
            gl_functions->glEnableVertexAttribArray(GLuint(i));
            gl_functions->glVertexAttribPointer(GLuint(i), attribute.numComponents, GL_FLOAT, GL_FALSE, vertexFormat.size, (void*)(attribute.offset));
        }
    }

    vertexbo.release();
    vertexbo.release();
    if(indexbo.isCreated())
        indexbo.release();

}

void SubMesh::Draw()
{
    int numVertices = dfileSize / vertexFormat.size;
    QOpenGLFunctions* glFunctions = QOpenGLContext::currentContext()->functions();

    vertexArray.bind();
    if (indexCount > 0)
    {
        glFunctions->glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glFunctions->glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }
    vertexArray.release();
}

void SubMesh::Destroy()
{
    if (vertexArray.isCreated())
        vertexArray.destroy();
    if (vertexbo.isCreated())
        vertexbo.destroy();
    if (indexbo.isCreated())
        indexbo.destroy();
}
