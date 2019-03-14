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
    explicit WidgetShapeRenderer(QWidget *parent = 0);
    ~WidgetShapeRenderer();

    void ConnectSignalsSlots();

public slots:

    void pushButton_fillColor();

private:

    Ui::WidgetShapeRenderer *ui;

};

#endif // WIDGETSHAPERENDERER_H
