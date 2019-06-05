#include "scene.h"
#include "hierarchy.h"
#include "inspector.h"
#include "meshrenderer.h"
#include "resourcemanager.h"
#include "light.h"
#include "transform.h"

Scene::Scene()
{
    //gameobjects = new QList<GameObject*>();
}

GameObject* Scene::CreateGameObject()
{
    GameObject *gameobject = new GameObject(GetUUID(), "GameObject" + GetCountUUID());
    gameobjects.push_back(gameobject);
    return gameobject;
}

void Scene::SyncWindows(Inspector* ins, Hierarchy* hie, ResourceManager* reM)
{
    inspector = ins;
    hierarchy = hie;
    resourceManager = reM;
}

void Scene::SaveScene(QJsonObject &json) const
{
    for(int i = 0; i < gameobjects.size(); i++)
    {
        QJsonObject gObject;
        QString name;
        name = "GameObject_" + QString::number(i);
        gameobjects.at(i)->Save(gObject);
        gObject["MeshRenderer"] = gameobjects[i]->GetMeshRenderer() != nullptr;
        gObject["Light"] = gameobjects[i]->GetLight() != nullptr;
        json[name] = gObject;
    }
    json["NumberOfGameObjects"] = gameobjects.size();
}

void Scene::LoadScene(const QJsonObject &json)
{
    int numGameObjects = json["NumberOfGameObjects"].toInt();
    for(int i = 0; i < numGameObjects; i++)
    {
        QJsonObject gObject;
        QString name;
        name = "GameObject_" + QString::number(i);
        gObject = json[name].toObject();
        GameObject* gameObject = CreateGameObject();
        gameObject->name = gObject["Name"].toString();
        hierarchy->AddGameObject(gameObject);
        if(gObject["MeshRenderer"].toBool())
            gameObject->AddMeshRenderer();
        if(gObject["Light"].toBool())
            gameObject->AddLight();
        gameObject->Load(gObject);
    }
}

void Scene::GameObjectHierarchyClicked(GameObject* gameobject)
{
    inspector->ShowGameObject(gameobject);
}

void Scene::RemoveGameObject(int uid)
{
    GameObject *go= gameobjects.at(uid);
    gameobjects.removeAt(uid);
    delete go;
}

int Scene::GetUUID()
{
    if(gameobjects.size() > 0)
        return gameobjects.size();
    else
        return 0;
}

QString Scene::GetCountUUID()
{
    QString ret = "";
    if(gameobjects.size() > 0)
    {

        ret = " (" + QString::number(gameobjects.size());
        ret += ")";
    }
    return ret;
}

void Scene::Draw()
{
    for(int i = 0; i < gameobjects.size(); i++)
    {
        gameobjects.at(i)->GetMeshRenderer()->Draw();
    }
}

void Scene::AddPrimitive(std::string primitive)
{
    GameObject *go = nullptr;
    if (primitive == "Sphere")
    {
        go = new GameObject(GetUUID(), "Sphere" + GetCountUUID());
    }
    else if (primitive == "Cube")
    {
        go = new GameObject(GetUUID(), "Cube" + GetCountUUID());
    }
    else if (primitive == "Cone")
    {
        go = new GameObject(GetUUID(), "Cone" + GetCountUUID());
    }
    else if (primitive == "Plane")
    {
        go = new GameObject(GetUUID(), "Plane" + GetCountUUID());
    }
    else if (primitive == "Torus")
    {
        go = new GameObject(GetUUID(), "Torus" + GetCountUUID());
    }
    else if (primitive == "Cylinder")
    {
        go = new GameObject(GetUUID(), "Cylinder" + GetCountUUID());
    }
    else if (primitive == "Pyramid")
    {
        go = new GameObject(GetUUID(), "Pyramid" + GetCountUUID());
    }

    if (go != nullptr)
    {
        go->AddMeshRenderer();
        go->GetMeshRenderer()->SetMesh((Mesh*)resourceManager->GetResourceObject(primitive + ".obj", ResourceType::RMesh));
        gameobjects.push_back(go);
        hierarchy->AddGameObject(go);
    }
    else
    {
        qInfo() << "Error with create Primitive";
    }
}

void Scene::AddLightSphere()
{
    GameObject *go = new GameObject(GetUUID(), "PointLight " + GetCountUUID());
    go->AddMeshRenderer();
    go->GetMeshRenderer()->SetMesh((Mesh*)resourceManager->GetResourceObject("Sphere.obj", ResourceType::RMesh));
    go->AddLight();
    go->GetLight()->SetType(1);
    go->GetLight()->SetRange(30);
    go->GetLight()->SetIntensity(50);
    go->GetTransform()->position = QVector3D(10, 10, 10);
    go->GetTransform()->scale = QVector3D(0.3f, 0.3f, 0.3f);
    gameobjects.push_back(go);
    hierarchy->AddGameObject(go);
}


















