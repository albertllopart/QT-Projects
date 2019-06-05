#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <QList>
#include "gameobject.h"

#include <QObject>
#include <QJsonObject>

class Inspector;
class Hierarchy;
class ResourceManager;

class Scene
{
public:
    Scene();


    GameObject* CreateGameObject();
    void SyncWindows(Inspector*,Hierarchy*,ResourceManager*);

    void SaveScene(QJsonObject &json) const;
    void LoadScene(const QJsonObject &json);
    void GameObjectHierarchyClicked(GameObject* gameobject);

    void Draw();

    int GetUUID();
    QString GetCountUUID();
    void RemoveGameObject(int uid);

    void AddPrimitive(std::string primitive);
    void AddLightSphere();

public:
    QList<GameObject*> gameobjects;
    Inspector* inspector = nullptr;
    Hierarchy* hierarchy = nullptr;
    ResourceManager* resourceManager = nullptr;
};

#endif // SCENE_H
