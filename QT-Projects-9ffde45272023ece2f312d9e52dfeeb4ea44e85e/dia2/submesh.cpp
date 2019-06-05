#include "submesh.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <stdio.h>
#include "texture.h"
#include "QImage"
#include "applicationqt.h"
#include "mainwindow.h"
#include "resourcemanager.h"

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size) : ibo(QOpenGLBuffer::IndexBuffer)
{
    this->vertexFormat = vertexFormat;
    memcpy(this->data, data, size);
    dataSize = size;
}

SubMesh::SubMesh(VertexFormat vertexFormat, void *data, int size, unsigned int *indices, int indicesCountP):
    ibo(QOpenGLBuffer::IndexBuffer)
{
    this->vertexFormat = vertexFormat;
    this->data = new uchar[size];
    memcpy(this->data, data, size);
    dataSize = size;

    indice = new unsigned int[(indicesCountP * sizeof(uint))];
    memcpy(indice, indices, (indicesCountP * sizeof(uint)));
    indicesCount = indicesCountP;
}

void SubMesh::Update()
{
    if(!vao.isCreated())
        vao.create();
    vao.bind();

    if(!vbo.isCreated())
        vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(data,int(dataSize));
    delete[] data;
    data = nullptr;

    if (indice != nullptr)
    {
        if(!ibo.isCreated())
           ibo.create();
        ibo.bind();
        ibo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        ibo.allocate(indice, int(indicesCount * sizeof ( unsigned int)));
        delete[] indice;
        indice = nullptr;
    }
    for (int location = 0; location < MAX_VERTEX_ATTRIBUTES; ++location)
    {
        VertexAttribute &attr = vertexFormat.attribute[location];
        if(attr.enabled)
        {
            //printf("%i ", location);
            GL->glEnableVertexAttribArray(GLuint(location));
            GL->glVertexAttribPointer(GLuint(location), attr.numComponents,
                                      GL_FLOAT, GL_FALSE,
                                      vertexFormat.size,
                                      (void*) (attr.offset));
        }
    }
    vao.release();
    vbo.release();
    if(ibo.isCreated())
        ibo.release();
}

void SubMesh::Draw()
{
    //qInfo() << "Draw...";
    texture->Draw();
    int numVertices = dataSize / vertexFormat.size;
    if(vao.isCreated())
    {
        vao.bind();
        if (indicesCount > 0)
            GL->glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
        else
            GL->glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }
    vao.release();
    texture->UnBind();
}

void SubMesh::Destroy()
{
    if(vbo.isCreated())
        vbo.destroy();
    if(ibo.isCreated())
        vbo.destroy();
    if(vao.isCreated())
        vbo.destroy();
}
