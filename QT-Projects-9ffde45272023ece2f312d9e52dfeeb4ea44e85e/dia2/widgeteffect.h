#ifndef WIDGETEFFECT_H
#define WIDGETEFFECT_H

#include <QWidget>

namespace Ui {
class WidgetEffect;
}

class WidgetEffect : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetEffect(QWidget *parent = nullptr);
    ~WidgetEffect();

    void ConnectSignalsSlots();
    void UpdateValues();

public slots:
    void UpdateLightSceneColor();
    void UpdateLightSceneIntensity(int value);
    void UpdateLightSceneRange(int value);

    void UpdateEffect(const QString& nameSubmesh);
    void UpdateIntensityBlur();
    void UpdateAcceptBloom();

private:
    Ui::WidgetEffect *ui;
};

#endif // WIDGETEFFECT_H
