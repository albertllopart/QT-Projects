#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
//#include "widget2dtransform.h"
//#include "widgetshaperenderer.h"
#include <QVBoxLayout>

namespace Ui {
class Inspector;
}
class GameObject;
class Scene;
class Widget2DTransform;
class Component;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(Scene* sceneA, QWidget *parent = nullptr);
    ~Inspector();

    void ShowGameObject(GameObject*);
    void DeleteLayout();

private:
    QWidget* GetWidget(Component* component);

public slots:
    void SetName(QString);
    void AddMeshRenderer();
    void AddLight();

public:
    GameObject* selected;

signals:
    void MainUpdate();

private:

    Ui::Inspector *ui;
    Scene* scene;
    QVBoxLayout *layout=nullptr;
};

#endif // INSPECTOR_H
