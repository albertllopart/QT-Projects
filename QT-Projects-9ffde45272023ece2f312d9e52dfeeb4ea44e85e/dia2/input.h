#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>
#include <qpoint.h>

enum class KeyState
{
    UP, PRESSED, DOWN
};

enum class MouseButtonState
{
    UP, PRESSED, DOWN
};

class MyOpenGLWidget;

class Input
{
public:
    Input(MyOpenGLWidget* parent);
    ~Input();

    //Event processing functions
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseWheelEvent(QWheelEvent* event);

    void postUpdate();
    void updateParameters(QMouseEvent* event);

    //translation
    QVector3D xLeft(float yaw, float pitch);
    QVector3D xRight(float yaw, float pitch);
    QVector3D yUp(float yaw, float pitch);
    QVector3D yDown(float yaw, float pitch);
    QVector3D zOnward(float yaw, float pitch);
    QVector3D zBackward(float yaw, float pitch);

    enum { MAX_BUTTONS = 10, MAX_KEYS = 300 };

    //keyboard state
    KeyState keys[MAX_KEYS];

    //mouse state
    MouseButtonState mouseButtons[MAX_BUTTONS];

    //easier with raw booleans
    bool rightMouse = false;
    bool leftMouse = false;
    bool midMouse = false;
    bool alt = false;

    QPoint mousePosition;
    int mouseX = 0;
    int mouseY = 0;
    int mouseX_prev = 0;
    int mouseY_prev = 0;

    MyOpenGLWidget* parent;
};

#endif // INPUT_H
