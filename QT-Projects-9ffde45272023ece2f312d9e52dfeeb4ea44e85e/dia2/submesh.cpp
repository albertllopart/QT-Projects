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
}
