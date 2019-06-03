#include "meshrenderer.h"
#include "mesh.h"
#include "submesh.h"
#include "texture.h"
#include "gameobject.h"
#include "applicationqt.h"
#include "mainwindow.h"
#include "resourcemanager.h"

MeshRenderer::MeshRenderer(GameObject* gameobject) : Component(gameobject, Type::ComponentMeshRenderer)
{
    name = "MeshRenderer";
}

void MeshRenderer::Draw()
{
    if(mesh != nullptr)
    {
        mesh->Update();
        mesh->Draw(material);
    }
}

void MeshRenderer::SetMesh(Mesh *mesh)
{
    this->mesh = mesh;
}

void MeshRenderer::SetMaterial(Material *material)
{
    this->material = material;
}

Mesh* MeshRenderer::GetMesh() const
{
    return mesh;
}

void MeshRenderer::Save(QJsonObject &json) const
{
    bool hasMesh = this->mesh != nullptr;
    json["HasMesh"] = hasMesh;
    if(this->mesh != nullptr)
    {
        json["MeshName"] = mesh->GetName();
        for(int i = 0; i < mesh->meshes.size(); i++)
        {
            QString meshid = "Texture_" + QString::number(i);
            json[meshid] = mesh->meshes[i]->texture->GetName();
        }
    }
}

void MeshRenderer::Load(const QJsonObject &json)
{
    bool hasMesh = json["HasMesh"].toBool();
    if(hasMesh)
    {
        std::string nameMesh = json["MeshName"].toString().toStdString();
        mesh = (Mesh*)App->Window()->GetResourceManager()->GetResourceObject(nameMesh, ResourceType::RMesh);
        for(int i = 0; i < mesh->meshes.size(); i++)
        {
            QString meshid = "Texture_" + QString::number(i);
            std::string nameTexture = json[meshid].toString().toStdString();
            Texture* texture = (Texture*)App->Window()->GetResourceManager()->GetResource(nameTexture);
            if(texture != nullptr)
                mesh->meshes[i]->texture = texture;
            else
                mesh->meshes[i]->texture = (Texture*)App->Window()->GetResourceManager()->GetResource(0, ResourceType::RTexture);
        }
    }
}








