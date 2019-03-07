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

private:

    Ui::Widget2DTransform *ui;

};

#endif // WIDGET2DTRANSFORM_H
