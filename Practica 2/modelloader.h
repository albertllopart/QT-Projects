#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <qvector.h>
#include <assimp/postprocess.h>

class ModelLoader
{
public:
    ModelLoader();



    void Load(const char* pathToFile);

    //QVector<SubMesh*> submeshes;

private:

    void processNode(aiNode* node, const aiScene* scene);
    //SubMesh* processNode(aiNode* node, const aiScene* scene);
};

#endif // MODELLOADER_H
