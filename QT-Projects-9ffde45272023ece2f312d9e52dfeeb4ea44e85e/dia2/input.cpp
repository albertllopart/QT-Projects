#include "input.h"
#include <QVector3D>
#include <QtMath>
#include <myopenglwidget.h>

Input::Input(MyOpenGLWidget* parent)
{
    this->parent = parent;
}

Input::~Input()
{

}

void Input::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt)
    {
        alt = true;
    }

    if (rightMouse == true)
    {
        float &yaw = parent->camera->yaw;
        float &pitch = parent->camera->pitch;

        QVector3D displacementVector;

        if (event->key() == Qt::Key_W)
        {
            displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                            sinf(qDegreesToRadians(pitch)),
                                            -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
        }
        if (event->key() == Qt::Key_A)
        {
            displacementVector += QVector3D(-cosf(qDegreesToRadians(yaw)),
                                            0.0f,
                                            sinf(qDegreesToRadians(yaw)));
        }
        if (event->key() == Qt::Key_S)
        {
            displacementVector += QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                            -sinf(qDegreesToRadians(pitch)),
                                            cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
        }
        if (event->key() == Qt::Key_D)
        {
            displacementVector += QVector3D(cosf(qDegreesToRadians(yaw)),
                                            0.0f,
                                            -sinf(qDegreesToRadians(yaw)));
        }

        displacementVector *= parent->camera->speed / 60.0f; //fake delta time

        parent->camera->position += displacementVector;

    }
}

void Input::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt)
    {
        alt = false;
    }
}

void Input::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();

    if(event->button() == Qt::RightButton)
    {
        rightMouse = true;
    }
    if(event->button() == Qt::LeftButton)
    {
        leftMouse = true;
    }
    if(event->button() == Qt::MidButton)
    {
        midMouse = true;
    }
}

void Input::mouseMoveEvent(QMouseEvent *event)
{

}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        rightMouse = false;
    }
    if(event->button() == Qt::LeftButton)
    {
        leftMouse = false;
    }
    if(event->button() == Qt::MidButton)
    {
        midMouse = false;
    }
}

void Input::mouseWheelEvent(QWheelEvent *event)
{

}
