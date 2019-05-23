#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <camera.h>

enum class KeyState
{
    UP, PRESSED, DOWN
};

enum class MouseButtonState
{
    UP, PRESSED, DOWN
};

class Input
{
public:

    Input()
    {

    }
    ~Input()
    {

    }

    //Event processing functions
    void keyPressEvent(QKeyEvent* event)
    {

    }
    void keyReleaseEvent(QKeyEvent* event)
    {

    }
    void mousePressEvent(QMouseEvent* event)
    {

    }
    void mouseMoveEvent(QMouseEvent* event)
    {

    }
    void mouseReleaseEvent(QMouseEvent* event)
    {

    }

    void postUpdate()
    {

    }

    enum { MAX_BUTTONS = 10, MAX_KEYS = 300 };

    //keyboard state
    KeyState keys[MAX_KEYS];

    //mouse state
    MouseButtonState mouseButtons[MAX_BUTTONS];
    int mouseX = 0;
    int mouseY = 0;
    int mouseX_prev = 0;
    int mouseY_prev = 0;
};

class MyOpenGLWidget :
        public QOpenGLWidget,
        protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:

    class Interaction
    {
    public:

        bool update();

    private:

        bool idle();
        bool navigate();
        bool focus() {return true;}
        bool translate() {return true;}
        bool rotate() {return true;}
        bool scale() {return true;}

        enum State { Idle, Navigating, Focusing, Translating, Rotating, Scaling };

        State state = State::Idle;

    };

    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget() override;

    //From these methods we can call OpenGL func
    //Virtual methods
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    //sample OpenGL
    void createSampleTriangle();

    //scene interaction
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

signals:

public slots:
    //Not virtual
    void finalizeGL();
    void frame();

private:

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

    //Default Shaders
    QString default_shader_vert =
    "#version 330 core\n"

    "layout(location=0) in vec3 position;\n"
    "layout(location=1) in vec3 color;\n"

    "out Data\n"
    "{\n"
        "vec3 color;\n"
    "} VSOut;\n"

    "void main(void)\n"
    "{\n"
        "gl_Position = vec4(position, 1);\n"
        "VSOut.color = color;\n"
    "}";
    int u_worldToCamera;
    int u_cameraToView;
    //Camera3D m_camera;

    QString default_shader_frag =
    "#version 330 core\n"

    "in Data\n"
    "{\n"
        "vec3 color;\n"
    "} FSIn;\n"

    "out vec4 outColor;\n"

    "void main(void)\n"
    "{\n"
        "outColor = vec4(FSIn.color, 1.0);\n"
    "}";

private:

    static Input* input;
    Interaction* interaction;
    QTimer timer;

    static Camera* camera;
};

#endif // MYOPENGLWIDGET_H
