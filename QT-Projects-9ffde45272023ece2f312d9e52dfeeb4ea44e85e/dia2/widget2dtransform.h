#ifndef WIDGET2DTRANSFORM_H
#define WIDGET2DTRANSFORM_H

#include <QWidget>

namespace Ui {
class Widget2DTransform;
}

class Transform;

class Widget2DTransform : public QWidget
{
    Q_OBJECT

public:

    explicit Widget2DTransform(Transform* transformGo, QWidget *parent = 0);
    ~Widget2DTransform();

    void ConnectSignalsSlots();

public slots:
    void UpdateTransform();

signals:
    void InspectorUpdate();

private:
    int initialSize = 5;
    Ui::Widget2DTransform *ui;
    Transform* transform = nullptr;
};

#endif // WIDGET2DTRANSFORM_H
