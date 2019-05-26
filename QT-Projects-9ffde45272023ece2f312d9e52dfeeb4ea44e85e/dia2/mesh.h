#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "assimp/mesh.h"
#include <qvector.h>
#include <assimp/postprocess.h>
#include <queue>
#include "resourcemanager.h"

class Material;
class SubMesh;

class Mesh : public Resource
{
public:
    Mesh();
    ~Mesh() override;

    void Draw(Material* material);
    void Draw() override;
    void Destroy() override;

    void Load(const char* pathToFile);
    std::vector<SubMesh*> meshes;

    //QVector<SubMesh*> submeshes;

private:

    void ProcessNodes(const aiScene* scene);
    void ProcessNode(aiNode* node, const aiScene* scene);
    SubMesh* ProcessSubMeshNode(aiMesh* node, const aiScene* scene);

    std::queue<aiNode*> nodes;
};

#endif // MESH_H
