#include "mesh.h"
#include "submesh.h"
#include "material.h"
#include <qfile.h>
#include <QOpenGLFunctions>
#include <QFileInfo>
#include <QDebug>

Mesh::Mesh(): Resource(RMesh)
{

}

Mesh::~Mesh()
{
    for(std::vector<SubMesh*>::iterator it = meshes.begin(); it != meshes.end(); it++)
    {
        if((*it) != nullptr)
            delete (*it);
    }

    meshes.clear();
}

void Mesh::Update()
{
    foreach (SubMesh* subMesh, meshes)
        subMesh->Update();
}

void Mesh::Draw(Material* material)
{
    int material_index = 0;
    foreach (SubMesh* subMesh, meshes)
    {
        if(material)
        {
            //material->Draw(material_index);
            material_index++;

        }
        subMesh->Draw();

        //if(material)
        //{
        //    material->UnBind();
        //}
    }
}

void Mesh::Draw()
{
    foreach (SubMesh* submesh, meshes)
    {
        submesh->Draw();
    }
}

void Mesh::Destroy()
{
    foreach (SubMesh* submesh, meshes) {
        submesh->Destroy();
    }
}

void Mesh::Load(const char* path)
{
    Assimp::Importer import;

    QFile file(path);
    qInfo() << "Path: " << path;
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

    ProcessNodes(scene->mRootNode, scene);
}

void Mesh::ProcessNodes(aiNode *node, const aiScene *scene)
{
    // ProcessNode
    ProcessNode(node, scene);

    for (uint i = 0; i < node->mNumChildren; i++)
    {
        ProcessNodes(node->mChildren[i], scene);
    }
}
void Mesh::ProcessNode(aiNode* node, const aiScene* scene)
{
    // Heee
    for (uint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
        SubMesh* sub = ProcessSubMeshNode(aiMesh, scene);

        if (sub != nullptr)
        {
            meshes.push_back(sub);
        }
    }
}

SubMesh* Mesh::ProcessSubMeshNode(aiMesh *mesh, const aiScene *scene)
{
    SubMesh* sub = nullptr;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    bool hasTexCoords = false;

    for(uint i = 0; i < mesh->mNumVertices; i++)
    {
        // Vertices
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        // Normals
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        // TextCoords
        if (mesh->mTextureCoords[0])
        {
            // Yes
            hasTexCoords = true;
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    //Proces Indicess
    for(uint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    VertexFormat format;
    format.SetVertexAttribute(0, 0, 3);
    format.SetVertexAttribute(1, 3 * sizeof(float), 3);

    if (hasTexCoords)
        format.SetVertexAttribute(2, 6 * sizeof(float), 2);

    sub = new SubMesh(format);

    // Now adding info...
    sub->SetInfo(vertices.size() * sizeof(float), indices.size(), &vertices[0], &indices[0]);

    sub->textureName = "NoN";
    sub->meshName = mesh->mName.C_Str();
    return sub;
}
