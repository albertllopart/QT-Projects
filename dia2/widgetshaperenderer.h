#ifndef WIDGETSHAPERENDERER_H
#define WIDGETSHAPERENDERER_H

#include <QWidget>

namespace Ui {
class WidgetShapeRenderer;
}

class WidgetShapeRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetShapeRenderer(QWidget *parent = 0);
    ~WidgetShapeRenderer();

private:
    Ui::WidgetShapeRenderer *ui;
};

#endif // WIDGETSHAPERENDERER_H
