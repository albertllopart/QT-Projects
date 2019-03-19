#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "widget2dtransform.h"
#include "widgetshaperenderer.h"

namespace Ui {
class Inspector;
}

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

private:

    Ui::Inspector *ui;
    Widget2DTransform *transform;
    WidgetShapeRenderer *renderer;
};

#endif // INSPECTOR_H
