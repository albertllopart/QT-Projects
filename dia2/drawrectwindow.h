#ifndef DRAWRECTWINDOW_H
#define DRAWRECTWINDOW_H

#include <QWidget>

namespace Ui {
class DrawRectWindow;
}

class DrawRectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DrawRectWindow(QWidget *parent = nullptr);
    ~DrawRectWindow() override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;


private:
    Ui::DrawRectWindow *ui;
};

#endif // DRAWRECTWINDOW_H
