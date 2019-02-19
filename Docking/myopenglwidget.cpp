#include "myopenglwidget.h"

#pragma comment( lib, "OpenGL32.lib" )

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{

}


void MyOpenGLWidget::initializeGL()
{

}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    this->setMinimumSize(width, height);
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.5, 0.7, 0.9, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
