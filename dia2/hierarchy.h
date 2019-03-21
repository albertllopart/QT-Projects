#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <QList>

namespace Ui {
class Hierarchy;
}
class Scene;
class QListWidgetItem;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(Scene* scene, QWidget *parent = nullptr);
    ~Hierarchy();

    void ConnectSignalsSlots();

signals:

public slots:

    void AddGameObject();
    void RemoveGameObject();
    void GameObjectClicked(QListWidgetItem* item);

private:
    Scene* scene;
    Ui::Hierarchy *ui;
    QList<int> *gameobjects;
};

#endif // HIERARCHY_H
