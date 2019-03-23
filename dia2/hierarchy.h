#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <QList>

namespace Ui {
class Hierarchy;
}
class Scene;
class QListWidgetItem;
class GameObject;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(Scene* scene, QWidget *parent = nullptr);
    ~Hierarchy();

    void ConnectSignalsSlots();

public slots:

    void AddGameObject(GameObject* gameobject);
    void RemoveGameObject();
    void GameObjectClicked(QListWidgetItem* item);
    void Update();
    void Testing();

public:
    Ui::Hierarchy *ui;

private:
    Scene* scene;
};

#endif // HIERARCHY_H
