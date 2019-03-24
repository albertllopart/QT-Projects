#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <QList>
#include "gameobject.h"

#include <QObject>

class Inspector;
class Hierarchy;

class Scene
{
public:
    Scene();


    GameObject* CreateGameObject();
    void SyncWindows(Inspector*,Hierarchy*);

    void SaveScene();
    void LoadScene();
    void GameObjectHierarchyClicked(GameObject* gameobject);

    int GetUUID();
    QString GetCountUUID();
    void RemoveGameObject(int uid);

public:
    QList<GameObject*> gameobjects;
    Inspector* inspector;
    Hierarchy* hierarchy;
};

#endif // SCENE_H
