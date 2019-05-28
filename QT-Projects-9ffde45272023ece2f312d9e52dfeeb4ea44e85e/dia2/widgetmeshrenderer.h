#ifndef WIDGETMESHRENDERER_H
#define WIDGETMESHRENDERER_H

#include <QWidget>

namespace Ui {
class WidgetMeshRenderer;
}

class MeshRenderer;
class Scene;

class WidgetMeshRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMeshRenderer(Scene* scene, MeshRenderer* mesh, QWidget *parent = nullptr);
    ~WidgetMeshRenderer();

    void ConnectSignalsSlots();

public slots:
    void UpdateMeshRenderer();
    void UpdateMaterial();

signals:
    void InspectorUpdate();

private:
    Ui::WidgetMeshRenderer *ui;
    MeshRenderer* mesh;
    Scene* scene;
};

#endif // WIDGETMESHRENDERER_H
