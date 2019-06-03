#ifndef WIDGETMESHRENDERER_H
#define WIDGETMESHRENDERER_H

#include <QWidget>

namespace Ui {
class WidgetMeshRenderer;
}

class MeshRenderer;
class Scene;
class Mesh;

class WidgetMeshRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMeshRenderer(Scene* scene, MeshRenderer* mesh, QWidget *parent = nullptr);
    ~WidgetMeshRenderer();

    void ConnectSignalsSlots();
    void ChangeMesh(QLayout* layout);
    void AddTexturesLayout(Mesh* mesh);

public slots:
    void UpdateMeshRenderer();
    void UpdateTexture(const QString&);

signals:
    void InspectorUpdate();

private:
    Ui::WidgetMeshRenderer *ui;
    MeshRenderer* meshRenderer;
    Scene* scene;
};

#endif // WIDGETMESHRENDERER_H
