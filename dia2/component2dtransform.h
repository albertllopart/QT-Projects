#ifndef COMPONENT2DTRANSFORM_H
#define COMPONENT2DTRANSFORM_H

#include <QWidget>

namespace Ui {
class Component2DTransform;
}

class Component2DTransform : public QWidget
{
    Q_OBJECT

public:

    explicit Component2DTransform(QWidget *parent = 0);
    ~Component2DTransform();

private:

    Ui::Component2DTransform *ui;

};

#endif // COMPONENT2DTRANSFORM_H
