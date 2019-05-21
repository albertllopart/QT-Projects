#include "scene.h"
#include "hierarchy.h"
#include "inspector.h"

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

void Scene::SyncWindows(Inspector* ins, Hierarchy* hie)
{
    inspector = ins;
    hierarchy = hie;
}

void Scene::SaveScene(QJsonObject &json) const
{
    for(int i = 0; i < gameobjects.size(); i++)
    {
        QJsonObject gObject;
        QString name;
        name = "GameObject_" + QString::number(i);
        gameobjects.at(i)->Save(gObject);
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
        hierarchy->AddGameObject(gameObject);
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

