#ifndef WIDGETSHAPERENDERER_H
#define WIDGETSHAPERENDERER_H

#include <QWidget>
#include <QColorDialog>

namespace Ui {
class WidgetShapeRenderer;
}

class WidgetShapeRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetShapeRenderer(QWidget *parent = nullptr);
    ~WidgetShapeRenderer();

    void ConnectSignalsSlots();
    void AdaptWidgetToEntity();
    void UpdateFillColor();
    void UpdateStrokeColor();

public slots:

    void UpdateShape();
    void UpdateSize();
    void OpenColorSelector();
    void UpdateStrokeThickness();
    void UpdateStrokeStyle();

private:

    Ui::WidgetShapeRenderer *ui;

};

#endif // WIDGETSHAPERENDERER_H
