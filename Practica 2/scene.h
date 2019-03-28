#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <QList>
#include "gameobject.h"

#include <QObject>
#include <QJsonObject>

class Inspector;
class Hierarchy;

class Scene
{
public:
    Scene();


    GameObject* CreateGameObject();
    void SyncWindows(Inspector*,Hierarchy*);

    void SaveScene(QJsonObject &json) const;
    void LoadScene(const QJsonObject &json);
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
