#include "meshrenderer.h"
#include "mesh.h"

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


