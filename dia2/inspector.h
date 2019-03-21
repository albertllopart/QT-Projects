#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "widget2dtransform.h"
#include "widgetshaperenderer.h"

namespace Ui {
class Inspector;
}
class GameObject;
class Scene;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(Scene* sceneA, QWidget *parent = nullptr);
    ~Inspector();

    void ShowGameObject(GameObject*);

private:

    Ui::Inspector *ui;
    Scene* scene;
    GameObject* selected;
    Widget2DTransform *transform;
    WidgetShapeRenderer *renderer;
};

#endif // INSPECTOR_H
