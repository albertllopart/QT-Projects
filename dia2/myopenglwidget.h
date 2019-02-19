#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>

class MyOpenGLWidget : public QOpenGLWidget
{
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);

    //From these methods we can call OpenGL func
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

signals:

public slots:
};

#endif // MYOPENGLWIDGET_H
