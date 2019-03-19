#ifndef WIDGET2DTRANSFORM_H
#define WIDGET2DTRANSFORM_H

#include <QWidget>

namespace Ui {
class Widget2DTransform;
}

class Widget2DTransform : public QWidget
{
    Q_OBJECT

public:

    explicit Widget2DTransform(QWidget *parent = 0);
    ~Widget2DTransform();

    void ConnectSignalsSlots();

public slots:

    void UpdateTransform();

private:

    Ui::Widget2DTransform *ui;

    int translation_x;
    int translation_y;

    int scale_x;
    int scale_y;
};

#endif // WIDGET2DTRANSFORM_H
