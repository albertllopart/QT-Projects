#include "modelloader.h"
#include <qfile.h>

ModelLoader::ModelLoader()
{

}


void ModelLoader::Load(const char* path)
{
    Assimp::Importer import;

    QFile file(path);
}
