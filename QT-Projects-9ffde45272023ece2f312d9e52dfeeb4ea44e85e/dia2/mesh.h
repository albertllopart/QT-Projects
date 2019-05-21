#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <qvector.h>
#include <assimp/postprocess.h>

class Mesh
{
public:
    Mesh();

    void Load(const char* pathToFile);

    //QVector<SubMesh*> submeshes;

private:

    void processNode(aiNode* node, const aiScene* scene);
    //SubMesh* processNode(aiNode* node, const aiScene* scene);
};

#endif // MESH_H
