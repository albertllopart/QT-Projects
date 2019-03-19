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

public slots:

    void UpdateShape();
    void UpdateSize();
    void UpdateFillColor();
    void UpdateStrokeColor();
    void UpdateStrokeThickness();
    void UpdateStrokeStyle();

private:

    Ui::WidgetShapeRenderer *ui;

};

#endif // WIDGETSHAPERENDERER_H
