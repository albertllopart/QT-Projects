#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Assimp/include/assimp/Importer.hpp"
#include "Assimp/include/assimp/postprocess.h"
#include "Assimp/include/assimp/scene.h"
#include "Assimp/include/assimp/mesh.h"

class ModelLoader
{
public:
    ModelLoader();



    void Load(const char* pathToFile);

    //QVector<SubMesh*> submeshes;

private:

    //void processNode(aiNode* node, const aiScene* scene());

};

#endif // MODELLOADER_H
