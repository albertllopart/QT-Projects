#ifndef WIDGETLIGHT_H
#define WIDGETLIGHT_H

#include <QWidget>

namespace Ui {
class WidgetLight;
}

class Scene;
class Light;

class WidgetLight : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetLight(Scene* scene, Light* light, QWidget *parent = nullptr);
    ~WidgetLight();

    void ConnectSignalsSlots();

public slots:
    void UpdateLightType();
    void UpdateLightColor();
    void UpdateLightIntensity(int value);
    void UpdateLightRange(int value);

signals:
    void InspectorUpdate();

private:
    Ui::WidgetLight *ui;
    Scene* scene;
    Light* light;
};

#endif // WIDGETLIGHT_H
