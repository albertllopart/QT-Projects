#include "resourcemanager.h"
#include <QListWidget>
#include <QLabel>
#include <QDir>
#include <QDirIterator>
#include <QVBoxLayout>
#include <QApplication>
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include <QDebug>

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{
    resourcesList = new QListWidget(parent);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(resourcesList);
    //
    setLayout(layout);
    //
    // Get Path Resources :D
    QDir dir(QApplication::applicationDirPath() + "/../../dia2/Models/");
    QDirIterator searcher(dir, QDirIterator::Subdirectories);

    while(searcher.hasNext())
    {
        if(searcher.fileInfo().suffix() != "")
            Import(searcher.filePath().toStdString());

        searcher.next();
    }
}

void ResourceManager::Import(std::string path)
{
    // Check type of resources
    std::string fileType = path.substr(path.find_last_of("."));

    // Mesh
    if(fileType == ".obj" || fileType == ".fbx" || fileType == ".OBJ" || fileType == ".FBX")
    {
        ImportMesh(path);
    }

    // Texture
    if(fileType == ".png" || fileType == ".jpg" || fileType == ".JPG" || fileType == ".PNG")
    {
        ImportTexture(path);
    }
}

void ResourceManager::ImportMesh(std::string path)
{
    Mesh* mesh = new Mesh();
    mesh->SetName(path.substr(path.find_last_of("/") + 1).c_str());
    mesh->Load(path.c_str());
    qInfo() << "LOADED MESH: " << mesh->GetName();
    resources.push_back(mesh);
    resourcesList->addItem(mesh->GetName());
}

void ResourceManager::ImportTexture(std::string path)
{
    Texture* texture = new Texture();
    texture->SetName(path.substr(path.find_last_of("/") + 1).c_str());

    texture->SetType(TextureType::Albedo);
    texture->SetPath(path);

    texture->Load();
    resources.push_back(texture);
    resourcesList->addItem(texture->GetName());
}

int ResourceManager::GetCountResources(ResourceType type)
{
    int index = 0;
    foreach(Resource* resource, resources)
    {
        if(resource->GetType() == type)
        {
            index++;
        }
    }
    return index;
}

Resource* ResourceManager::GetResource(int i, ResourceType type)
{
    int index = 0;
    foreach(Resource* resource, resources)
    {
        if (resource->GetType() == type)
        {
            if(index == i)
                return resource;
            index++;
        }
    }
    return nullptr;
}
