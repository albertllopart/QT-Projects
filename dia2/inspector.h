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

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(Scene* sceneA, QWidget *parent = nullptr);
    ~Inspector();

    void ShowGameObject(GameObject*);
    void DeleteLayout();

public slots:
    void SetName(QString);

public:
    GameObject* selected;

private:

    Ui::Inspector *ui;
    Scene* scene;

    //Widget2DTransform *transform;
    //WidgetShapeRenderer *renderer;
    QVBoxLayout *layout=nullptr;
};

#endif // INSPECTOR_H
