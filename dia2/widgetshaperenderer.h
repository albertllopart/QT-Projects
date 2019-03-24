#ifndef WIDGETSHAPERENDERER_H
#define WIDGETSHAPERENDERER_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class WidgetShapeRenderer;
}

class ShapeRenderer;

class WidgetShapeRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetShapeRenderer(ShapeRenderer* rendererGo, QWidget *parent = nullptr);
    ~WidgetShapeRenderer();

    void ConnectSignalsSlots();
    void AdaptWidgetToEntity();

public slots:

    void UpdateShape();
    void UpdateSize();
    void UpdateStrokeThickness();
    void UpdateStrokeStyle();
    void UpdateFillColor();
    void UpdateStrokeColor();

signals:

    void InspectorUpdate();

private:

    Ui::WidgetShapeRenderer *ui;
    ShapeRenderer* renderer;
};

#endif // WIDGETSHAPERENDERER_H
