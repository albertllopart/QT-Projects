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

void Scene::GameObjectHierarchyClicked(int uid)
{
    for(int i = 0; i < gameobjects.size(); i++)
    {
        GameObject* gameobject = gameobjects[i];
        if(gameobject->uuid == uid)
        {
            inspector->ShowGameObject(gameobject);
            break;
        }
    }
}

void Scene::RemoveGameObject(int uid)
{
    GameObject* gameobjectToRemove;
    for(int i = 0; i < gameobjects.size(); i++)
    {
        gameobjectToRemove = gameobjects[i];
        if(gameobjectToRemove->uuid == uid)
        {
            if(inspector->selected == gameobjectToRemove)
            {
                inspector->DeleteLayout();
            }
            gameobjects.removeOne(gameobjectToRemove);
            break;
        }
    }
}

int Scene::GetUUID()
{
    return gameobjects.size() + 1;
}
