#ifndef DRAWRECT_H
#define DRAWRECT_H

#include <QWidget>

class drawRect : public QWidget
{
    Q_OBJECT

public:
    explicit drawRect(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;

};

#endif // DRAWRECT_H
