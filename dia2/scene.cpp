#include "scene.h"
#include "hierarchy.h"
#include "inspector.h"

Scene::Scene()
{
    //gameobjects = new QList<GameObject*>();
}

GameObject* Scene::CreateGameObject()
{
    GameObject *gameobject = new GameObject(GetUUID(), "Empty");
    gameobjects.push_back(gameobject);
    return gameobject;
}

void Scene::SyncWindows(Inspector* ins, Hierarchy* hie)
{
    inspector = ins;
    hierarchy = hie;
}

void Scene::SaveScene()
{

}
void Scene::LoadScene()
{

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
