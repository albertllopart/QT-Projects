#include "resourcemanager.h"
#include <QListWidget>
#include <QLabel>
#include <QDir>
#include <QDirIterator>
#include <QVBoxLayout>
#include <QApplication>
#include "mesh.h"
#include "submesh.h"
#include "material.h"
#include "texture.h"
#include <QDebug>

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{
    resourcesList = new QListWidget(parent);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(resourcesList);
    setLayout(layout);
}

void ResourceManager::ImportAssets()
{
    QDir dir(QApplication::applicationDirPath() + "/../../dia2/Models/");
    QDirIterator searcher(dir, QDirIterator::Subdirectories);

    ImportTexture("Texture/Checker.jpg");
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
    mesh->SetPath(path.c_str());
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

    //texture->Load();
    resources.push_back(texture);
    resourcesList->addItem(texture->GetName());
}

void ResourceManager::FixedResources()
{
    // Fixed Textures in SubMesh
    for(int i = 0; i < GetCountResources(ResourceType::RMesh); i++)
    {
        Mesh* mesh = ((Mesh*)GetResource(i, ResourceType::RMesh));
        for(int j = 0; j < mesh->meshes.size(); j++)
        {
            mesh->meshes[j]->texture = (Texture*)GetResource(0, ResourceType::RTexture);
        }
    }
    // Load Textures
    for(int i = 0; i < GetCountResources(ResourceType::RTexture); i++)
    {
        ((Texture*)GetResource(i, ResourceType::RTexture))->Load();
    }
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
            {
                //return GetResourceCopy(resource, type);
                return resource;
            }
            index++;
        }
    }
    return nullptr;
}

Resource* ResourceManager::GetResourceObject(int i, ResourceType type)
{
    int index = 0;
    foreach(Resource* resource, resources)
    {
        if (resource->GetType() == type)
        {
            if(index == i)
            {
                return GetResourceCopy(resource, type);
                //return resource;
            }
            index++;
        }
    }
    return nullptr;
}

Resource* ResourceManager::GetResource(std::string name)
{
    foreach(Resource* resource, resources)
    {
        if (resource->GetName() == name)
            return resource;
    }
    return nullptr;
}

Resource* ResourceManager::GetResourceCopy(Resource* copy, ResourceType type)
{
    if (type == ResourceType::RMesh)
    {
        Mesh* mesh = new Mesh();
        mesh->SetName(copy->GetName());
        mesh->SetPath(copy->GetPath());
        mesh->Load(copy->GetPath());
        for(int j = 0; j < mesh->meshes.size(); j++)
        {
            mesh->meshes[j]->texture = (Texture*)GetResource(0, ResourceType::RTexture);
        }
        return mesh;
    }
}


