#include "myopenglwidget.h"
#include <iostream>
#include <QDir>
#include <QtMath>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256, 256));

    setMouseTracking(true);
    input = new Input();
    interaction = new Interaction(this);
    camera = new Camera();

    //timer per cridar slot a cada frame
    connect(&timer, SIGNAL(timeout()), this, SLOT(frame()));

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
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    delete input;
    makeCurrent();
    finalizeGL();
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();


    u_worldToCamera = program.uniformLocation("worldToCamera");
    u_cameraToView = program.uniformLocation("cameraToView");

    //Handle context destructions
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(finalizeGL()));

    createSampleTriangle();
}

void MyOpenGLWidget::resizeGL(int width, int height)
{
    //TODO: resize textures
    // Set the viewport to window dimensions
    glViewport( 0, 0, width, qMax( height, 1 ) );
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(0.1f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //program.setUniformValue(u_worldToCamera, )
    if(program.bind())
    {
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vao.release();
        program.release();
    }

    //resourceManager->updateResources();

    camera->prepareMatrices();

    //renderer->render(camera);
}

void MyOpenGLWidget::finalizeGL()
{
    std::cout << "finalizeGL()" << std::endl;
}

void MyOpenGLWidget::frame()
{
    bool interacted = interaction->update();

    if (interacted)
    {
        update();
    }

    input->postUpdate();
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

//scene interaction
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

void MyOpenGLWidget::enterEvent(QEvent*)
{
    grabKeyboard();
}

void MyOpenGLWidget::leaveEvent(QEvent*)
{
    releaseKeyboard();
}

//class Input

//class Interaction
bool MyOpenGLWidget::Interaction::update()
{
    bool changed = false;

    switch(state)
    {
        case State::Idle:
        {
            changed = idle();
            break;
        }
        case State::Navigating:
        {
            changed = navigate();
            break;
        }
        case State::Focusing:
        {
            changed = focus();
            break;
        }
        case State::Translating:
        {
            changed = translate();
            break;
        }
        case State::Rotating:
        {
            changed = rotate();
            break;
        }
        case State::Scaling:
        {
            changed = scale();
            break;
        }
    }

    return changed;
}

bool MyOpenGLWidget::Interaction::idle()
{
    if (parent->input->mouseButtons[Qt::RightButton] == MouseButtonState::DOWN)
    {
        state = State::Navigating;
    }
    else if (parent->input->mouseButtons[Qt::LeftButton] == MouseButtonState::PRESSED)
    {
        QVector3D rayWorldSpace = parent->camera->screenPointToWorldRay(parent->input->mouseX, parent->input->mouseY);
        //todo:
        //crear una entity i fer-la servir per cridar flow de selecció
        return true;
    }
    else if (false /* si hi ha una entity seleccionada*/)
    {
        if (parent->input->keys[Qt::Key_F] == KeyState::PRESSED)
        {
            state = State::Focusing;
        }
        else if (parent->input->keys[Qt::Key_T] == KeyState::PRESSED)
        {
            state = State::Translating;
        }
        else if (parent->input->keys[Qt::Key_R] == KeyState::PRESSED)
        {
            state = State::Rotating;
        }
        else if (parent->input->keys[Qt::Key_S] == KeyState::PRESSED)
        {
            state = State::Scaling;
        }
    }

    return false;
}

bool MyOpenGLWidget::Interaction::navigate()
{
    if (parent->input->mouseButtons[Qt::RightButton] != MouseButtonState::DOWN)
    {
        state = State::Idle;
        return false;
    }

    bool cameraChanged = false;

    int mouseX_delta = parent->input->mouseX - parent->input->mouseX_prev;
    int mouseY_delta = parent->input->mouseY - parent->input->mouseY_prev;

    float &yaw = parent->camera->yaw;
    float &pitch = parent->camera->pitch;

    //camera navigation
    if (mouseX_delta != 0 || mouseY_delta != 0)
    {
        cameraChanged = true;
        yaw -= 0.3f * mouseX_delta;
        pitch -= 0.3f * mouseY_delta;
        while (yaw < 0.0f) yaw += 360.0f;
        while (yaw > 360.0f) yaw -= 360.0f;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    QVector3D displacementVector;

    if (parent->input->keys[Qt::Key_W] == KeyState::DOWN)
    {
        cameraChanged = true;
        displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    //todo
    //aquesta part de baix és un copia i enganxa de la de dalt, falta canviar alguns signes i cosf/sinf
    if (parent->input->keys[Qt::Key_A] == KeyState::DOWN)
    {
        cameraChanged = true;
        displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if (parent->input->keys[Qt::Key_S] == KeyState::DOWN)
    {
        cameraChanged = true;
        displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }
    if (parent->input->keys[Qt::Key_D] == KeyState::DOWN)
    {
        cameraChanged = true;
        displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    displacementVector *= parent->camera->speed / 60.0f; //fake delta time

    parent->camera->position += displacementVector;

    return cameraChanged;
}

