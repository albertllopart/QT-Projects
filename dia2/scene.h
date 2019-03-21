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
    void GameObjectHierarchyClicked(int uid);

    int GetUUID();

public:
    QList<GameObject*>* gameobjects;
    Inspector* inspector;
    Hierarchy* hierarchy;
};

#endif // SCENE_H
