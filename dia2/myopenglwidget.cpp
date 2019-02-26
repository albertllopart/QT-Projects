#include "myopenglwidget.h"
#include <iostream>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256, 256));
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    makeCurrent();
    finalizeGL();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    //Program
    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag");
    program.link();
    program.bind();

    //VBO
    QVector3D vertices[] = {
        QVector3D(-0.5f, -0.5f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f), //vertex 1
        QVector3D( 0.5f, -0.5f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f), //vertex 2
        QVector3D( 0.0f,  0.5f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f), //vertex 3
    };
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices, 6 * sizeof(QVector3D));

    //VAO: Captures state of VBO
    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount, GL_FLOAT, GL_FALSE, strideBytes, (void*)(offsetBytes1));

    //Release
    vao.release();
    vbo.release();
    program.release();
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    //TODO: resize textures
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.9f, 0.85f, 1.0f, 1.0f);

    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }

    glClear(GL_COLOR_BUFFER_BIT);
}

void MyOpenGLWidget::finalizeGL()
{
    std::cout << "finalizeGL()" << std::endl;
}


