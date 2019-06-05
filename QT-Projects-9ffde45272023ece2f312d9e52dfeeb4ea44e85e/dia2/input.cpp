#include "input.h"
#include <QVector3D>
#include <QtMath>
#include <myopenglwidget.h>
#include <QMessageLogger>
#include <applicationqt.h>
#include <mainwindow.h>

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
            displacementVector += zOnward(yaw, pitch);
        }
        if (event->key() == Qt::Key_A)
        {
            displacementVector += xLeft(yaw, pitch);
        }
        if (event->key() == Qt::Key_S)
        {
            displacementVector += zBackward(yaw, pitch);
        }
        if (event->key() == Qt::Key_D)
        {
            displacementVector += xRight(yaw, pitch);
        }

        displacementVector *= parent->camera->speed / 60.0f; //fake delta time

        parent->camera->position += displacementVector;

        App->Window()->updateGameObject();
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
    QVector3D displacementVector;

    float &yaw = parent->camera->yaw;
    float &pitch = parent->camera->pitch;

    if (event->delta() < 0)
    {
        displacementVector += zBackward(yaw, pitch);

        displacementVector *= parent->camera->speed / 60.0f; //fake delta time

        parent->camera->position += displacementVector;
    }
    else if (event->delta() > 0)
    {
        displacementVector += zOnward(yaw, pitch);

        displacementVector *= parent->camera->speed / 60.0f; //fake delta time

        parent->camera->position += displacementVector;
    }

    App->Window()->updateGameObject();
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    updateParameters(event);

    QVector3D displacementVector;

    float &yaw = parent->camera->yaw;
    float &pitch = parent->camera->pitch;

    if (midMouse == true)
    {
        if (mouseX - mouseX_prev > 0)
        {
            displacementVector += xLeft(yaw, pitch);
            displacementVector *= parent->camera->speed / 30.0f; //fake delta time
            parent->camera->position += displacementVector;
        }
        else if (mouseX - mouseX_prev < 0)
        {
            displacementVector += xRight(yaw, pitch);
            displacementVector *= parent->camera->speed / 30.0f; //fake delta time
            parent->camera->position += displacementVector;
        }

        if (mouseY - mouseY_prev > 0)
        {
            displacementVector += yDown(yaw, pitch);
            displacementVector *= parent->camera->speed / 30.0f; //fake delta time
            parent->camera->position += displacementVector;
        }
        else if (mouseY - mouseY_prev < 0)
        {
            displacementVector += yUp(yaw, pitch);
            displacementVector *= parent->camera->speed / 30.0f; //fake delta time
            parent->camera->position += displacementVector;
        }
    }

    if (rightMouse == true)
    {
        //camera navigation
        int mouseX_delta = mouseX - mouseX_prev;
        int mouseY_delta = mouseY - mouseY_prev;

        if (mouseX_delta != 0 || mouseY_delta != 0)
        {
            yaw -= 0.3f * mouseX_delta;
            pitch -= 0.3f * mouseY_delta;
            while (yaw < 0.0f) yaw += 360.0f;
            while (yaw > 360.0f) yaw -= 360.0f;
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;

            parent->camera->yaw = yaw;
            parent->camera->pitch = pitch;
        }
    }

    App->Window()->updateGameObject();
}

void Input::postUpdate()
{

}

void Input::updateParameters(QMouseEvent* event)
{
    mouseX_prev = mouseX;
    mouseY_prev = mouseY;

    mouseX = event->pos().x();
    mouseY = event->pos().y();
}

QVector3D Input::xLeft(float yaw, float pitch)
{
    return QVector3D(-cosf(qDegreesToRadians(yaw)),
                     0.0f,
                     sinf(qDegreesToRadians(yaw)));
}

QVector3D Input::xRight(float yaw, float pitch)
{
    return QVector3D(cosf(qDegreesToRadians(yaw)),
                     0.0f,
                     -sinf(qDegreesToRadians(yaw)));
}

QVector3D Input::yUp(float yaw, float pitch)
{
    return QVector3D(sinf(qDegreesToRadians(yaw)),
                     -cosf(qDegreesToRadians(pitch)),
                     -cosf(qDegreesToRadians(yaw)) * sinf(qDegreesToRadians(pitch)));
}

QVector3D Input::yDown(float yaw, float pitch)
{
    return QVector3D(-sinf(qDegreesToRadians(yaw)),
                     cosf(qDegreesToRadians(pitch)),
                     cosf(qDegreesToRadians(yaw)) * sinf(qDegreesToRadians(pitch)));
}

QVector3D Input::zOnward(float yaw, float pitch)
{
    return QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                     sinf(qDegreesToRadians(pitch)),
                     -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
}

QVector3D Input::zBackward(float yaw, float pitch)
{
    return QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                     -sinf(qDegreesToRadians(pitch)),
                     cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
}
