#include "myopenglwidget.h"
#include <iostream>
#include <QDir>
#include <QtMath>
#include <QOpenGLShader>
#include "scene.h"
#include "applicationqt.h"
#include "deferredrenderer.h"

QOpenGLFunctions_3_3_Core *GL;

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256, 256));

    setMouseTracking(true);


    //timer per cridar slot a cada frame
    connect(&timer, SIGNAL(timeout()), this, SLOT(frame()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateDT()));

    if (format().swapInterval() == -1)
    {
        // V_blank synchronization not available (tearing likely to happen)
        qDebug("Swap Buffers at V_blank not available: refresh at approx 60 fps.");
        timer.setInterval(17);
    }
    else
    {
        qInfo("V_blank synchronization available.");
        timer.setInterval(0);
    }
    timer.start();

    App->SetMyOpenGLWidget(this);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    delete input;
    makeCurrent();
    finalizeGL();
}

void MyOpenGLWidget::initializeGL()
{
    makeCurrent();
    deferredRenderer = new DeferredRenderer();
    input = new Input(this);
    camera = new Camera();
    camera->viewportWidth = this->width();
    camera->viewportHeight = this->height();

    GL = this;

    initializeOpenGLFunctions();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    deferredRenderer->InitDeferredRenderer();
    deferredRenderer->Resize(this->width(),this->height());

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    //createSampleTriangle();
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    camera->viewportWidth = this->width();
    camera->viewportHeight = this->height();
    // Resize textures;
    deferredRenderer->DeleteBuffers();
    deferredRenderer->Resize(width, height);
}

void MyOpenGLWidget::paintGL()
{
    camera->prepareMatrices();
    deferredRenderer->Render(camera);
}

void MyOpenGLWidget::finalizeGL()
{
    std::cout << "finalizeGL()" << std::endl;
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void MyOpenGLWidget::frame()
{
    /*bool interacted = interaction->update();

    if (interacted)
    {
        update();
    }

    input->postUpdate();*/
}

void MyOpenGLWidget::createSampleTriangle()
{
    //Program
    program.create();
    //program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/shader1_vert");
    //program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/shader1_frag");
    program.addShaderFromSourceCode(QOpenGLShader::Vertex, default_shader_vert);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, default_shader_frag);
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

void MyOpenGLWidget::updateDT()
{

}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    input->keyPressEvent(event);
}

void MyOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    input->keyReleaseEvent(event);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    input->mousePressEvent(event);
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    input->mouseMoveEvent(event);
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    input->mouseReleaseEvent(event);
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    input->mouseWheelEvent(event);
}

void MyOpenGLWidget::enterEvent(QEvent*)
{
    grabKeyboard();
}

void MyOpenGLWidget::leaveEvent(QEvent*)
{
    releaseKeyboard();
}

