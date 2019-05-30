#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "component.h"
class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
    MeshRenderer(GameObject* gameobject);

    void Draw();

    //void Save(QJsonObject &json) const override;
    //void Load(const QJsonObject &json) override;

    void SetMesh(Mesh* mesh);
    void SetMaterial(Material* material);

    Mesh* GetMesh() const;


private:
    Mesh* mesh = nullptr;
    Material* material = nullptr;

};

#endif // MESHRENDERER_H
