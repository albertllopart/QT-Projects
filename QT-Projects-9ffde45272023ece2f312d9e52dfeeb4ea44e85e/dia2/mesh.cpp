#include "mesh.h"

#include <qfile.h>
#include <QDebug>

Mesh::Mesh()
{

}

void Mesh::Load(const char* path)
{
    Assimp::Importer import;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        qInfo() << "Could open file";
        return;
    }

    QByteArray data = file.readAll();

    const aiScene* scene = import.ReadFileFromMemory(
                data.data(), data.size(),
                aiProcess_Triangulate |
                aiProcess_FlipUVs |
                aiProcess_GenSmoothNormals |
                aiProcess_OptimizeMeshes |
                aiProcess_PreTransformVertices |
                aiProcess_ImproveCacheLocality ,
                ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qInfo() << "Error Loading... (Assimp)";
        return;
    }

    processNode(scene->mRootNode, scene);
}


void Mesh::processNode(aiNode* node, const aiScene* scene)
{
    QVector<float> vertices;
    QVector<unsigned int> indices;

    bool hasTexCoords = false;

    // Process vertices
    //for (unsigned int i = 0; i < node->mNumMeshes)
}
