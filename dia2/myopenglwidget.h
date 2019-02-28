#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget* parent = nullptr);
    ~MyOpenGLWidget() override;

    //From these methods we can call OpenGL func
    //Virtual methods
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    //sample OpenGL
    void createSampleTriangle();

signals:

public slots:
    //Not virtual
    void finalizeGL();

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


};

#endif // MYOPENGLWIDGET_H
