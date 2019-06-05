#include "deferredrenderer.h"
#include <qopengl.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include "myopenglwidget.h"
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "applicationqt.h"
#include "mainwindow.h"
#include "scene.h"
#include "gameobject.h"
#include "light.h"
#include "transform.h"
#include "qopenglframebufferobject.h"
#include "meshrenderer.h"

DeferredRenderer::DeferredRenderer()
{
    sceneLightInit.Position = QVector3D(100, 100, 100);
    sceneLightInit.Color = QVector3D(0.75, 0.75, 0.75);
    sceneLightInit.TypeLight = 0;
    sceneLightInit.Intensity = 10.0;
    sceneLightInit.Radius = 0.0;
}

/*void DeferredRenderer::passGrid(Camera *camera)
{
    GLenum drawBuffers = GL_COLOR_ATTACHMENT3;
    glDrawBuffer(drawBuffers);

}*/

/*void DeferredRenderer::LoadGridProgram(const char *path)
{

}*/

void DeferredRenderer::InitDeferredRenderer()
{

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/GeometryShader.vert");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/GeometryShader.frag");
    program.link();

    programLight.create();
    programLight.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/LightShader.vert");
    programLight.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/LightShader.frag");
    programLight.link();

    //programGrid.create();
    //programGrid.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/GridShader.vert");
    //programGrid.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/GridShader.frag");
    //programGrid.link();

    programBloom.create();
    programBloom.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/BloomShader.vert");
    programBloom.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/BloomShader.frag");
    programBloom.link();

    programBlur.create();
    programBlur.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/GaussianBlurrShader.vert");
    programBlur.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/GaussianBlurrShader.frag");
    programBlur.link();

    programFinalBloom.create();
    programFinalBloom.addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/BloomFinalShader.vert");
    programFinalBloom.addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/BloomFinalShader.frag");
    programFinalBloom.link();
    //programFinalBloom
}

void DeferredRenderer::DeleteBuffers()
{
    GL->glDeleteTextures(1, &colorTexture);
    GL->glDeleteTextures(1, &normalTexture);
    GL->glDeleteTextures(1, &depthTexture);
    GL->glDeleteTextures(1, &positionTexture);
    GL->glDeleteFramebuffers(1, &fbo);

    GL->glDeleteTextures(1, &lighting);
    GL->glDeleteFramebuffers(1, &lightingfbo);
    GL->glDeleteTextures(1, &blurHV);
    GL->glDeleteFramebuffers(1, &blurfbo);
    GL->glDeleteTextures(1, &bloomfbo);
    GL->glDeleteFramebuffers(1, &bloom);
    GL->glDeleteTextures(1, &finalBloom);
    GL->glDeleteFramebuffers(1, &finalBloomfbo);
}

void DeferredRenderer::Resize(int width,int height)
{
    // Color
    GL->glGenTextures(1, &colorTexture);
    GL->glBindTexture(GL_TEXTURE_2D, colorTexture);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Normal
    GL->glGenTextures(1, &normalTexture);
    GL->glBindTexture(GL_TEXTURE_2D, normalTexture);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Position
    GL->glGenTextures(1, &positionTexture);
    GL->glBindTexture(GL_TEXTURE_2D, positionTexture);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Depth
    GL->glGenTextures(1, &depthTexture);
    GL->glBindTexture(GL_TEXTURE_2D, depthTexture);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    // Frame Buffer
    GL->glGenFramebuffers(1, &fbo);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, positionTexture, 0);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 , GL_COLOR_ATTACHMENT2};
    GL->glDrawBuffers(3, buffers);

    GL->glGenTextures(1, &lighting);
    GL->glBindTexture(GL_TEXTURE_2D, lighting);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Frame Buffer
    GL->glGenFramebuffers(1, &lightingfbo);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, lightingfbo);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lighting, 0);
    GL->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GL->glGenTextures(1, &blurHV);
    GL->glBindTexture(GL_TEXTURE_2D, blurHV);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Frame Buffer
    GL->glGenFramebuffers(1, &blurfbo);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, blurfbo);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurHV, 0);
    GL->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GL->glGenTextures(1, &bloom);
    GL->glBindTexture(GL_TEXTURE_2D, bloom);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Frame Buffer
    GL->glGenFramebuffers(1, &bloomfbo);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, bloomfbo);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloom, 0);
    GL->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GL->glGenTextures(1, &finalBloom);
    GL->glBindTexture(GL_TEXTURE_2D, finalBloom);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    GL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GL->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Frame Buffer
    GL->glGenFramebuffers(1, &finalBloomfbo);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, finalBloomfbo);
    GL->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalBloom, 0);
    GL->glDrawBuffer(GL_COLOR_ATTACHMENT0);



    GLenum status = GL->glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch(status)
    {
    case GL_FRAMEBUFFER_COMPLETE: // Everything's OK
    break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    qInfo() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
    qInfo() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
    qInfo() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
    qInfo() << "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
    qInfo() << "Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED"; break;
    default:
    qInfo() << "Framebuffer ERROR: Unknown ERROR";
    }


}


void DeferredRenderer::Render(Camera *camera)
{
    //qInfo() << "Render";
    GL->glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    PassMeshes(camera);
    //PassBloom(camera);
    if(App->Window()->showEffect == 0)
    {
        QOpenGLFramebufferObject::bindDefault();
        PassLight(camera);
    }
    if(App->Window()->showEffect == 1)
    {
        PassGaussianBlur(camera);
    }
    if(App->Window()->showEffect == 2)
    {
        PassBloom(camera);
    }
}

void DeferredRenderer::PassMeshes(Camera* camera)
{
    //GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 , GL_COLOR_ATTACHMENT2};
    //GL->glDrawBuffers(3, buffers);

    if(program.bind())
    {
        GL->glUniformMatrix4fv(program.uniformLocation("projectionMatrix"), 1, GL_FALSE, camera->projectionMatrix.data());
        foreach (GameObject* go, App->GetScene()->gameobjects)
        {
            if(go->GetMeshRenderer() != nullptr)
            {
                GL->glUniformMatrix4fv(program.uniformLocation("modelViewMatrix"),
                                       1,
                                       GL_FALSE,
                                       (camera->viewMatrix * go->GetTransform()->GetTransformMatrix()).data());
                GL->glUniformMatrix4fv(program.uniformLocation("modelWorldMatrix"),
                                       1,
                                       GL_FALSE,
                                       go->GetTransform()->GetTransformMatrix().data());

                GL->glActiveTexture(GL_TEXTURE0);
                go->GetMeshRenderer()->Draw();
            }
        }
    }
    program.release();
}

void DeferredRenderer::PassGrid(Camera* camera)
{

}

void DeferredRenderer::PassLight(Camera* camera)
{
    //->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    if(programLight.bind())
    {
        programLight.setUniformValue(programLight.uniformLocation("gAlbedo"), 0);
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, colorTexture);

        programLight.setUniformValue(programLight.uniformLocation("gNormal"), 1);
        GL->glActiveTexture(GL_TEXTURE1);
        GL->glBindTexture(GL_TEXTURE_2D, normalTexture);

        programLight.setUniformValue(programLight.uniformLocation("gPosition"), 2);
        GL->glActiveTexture(GL_TEXTURE2);
        GL->glBindTexture(GL_TEXTURE_2D, positionTexture);

        programLight.setUniformValue(programLight.uniformLocation("renderView"), renderView);

        int NumberLightsInScene = 0;
        lights.clear();
        if (App->Window()->showLightScene)
        {
            lights.push_back(sceneLightInit);
            NumberLightsInScene++;
        }
        //qInfo() << "NumberLight: " << NumberLightsInScene;
        foreach (GameObject* go, App->GetScene()->gameobjects)
        {
            if(go->GetLight() != nullptr)
            {
                LightScene sceneLight;
                sceneLight.Position = go->GetTransform()->position;

                sceneLight.Color = QVector3D((float)go->GetLight()->GetColor().red() / 255.0f,
                                             (float)go->GetLight()->GetColor().green() / 255.0f,
                                             (float)go->GetLight()->GetColor().blue() / 255.0f);
                sceneLight.TypeLight = go->GetLight()->GetType();
                sceneLight.Intensity = go->GetLight()->GetIntensity();
                sceneLight.Radius = go->GetLight()->GetRange();
                lights.push_back(sceneLight);
                NumberLightsInScene++;
            }
        }
        programLight.setUniformValue(programLight.uniformLocation("NumberLightsInScene"), NumberLightsInScene);

        for(int i = 0; i < lights.size(); i++)
        {
            //qInfo() << "Inte" << lights[i].Intensity;
            GL->glUniform3fv(GL->glGetUniformLocation(programLight.programId(),
                                                      ("lights["+QString::number(i)+"].Position").toStdString().c_str()),
                                                        1,
                                                        &lights[i].Position[0]);
            GL->glUniform3fv(GL->glGetUniformLocation(programLight.programId(),
                                                      ("lights["+QString::number(i)+"].Color").toStdString().c_str()),
                                                        1,
                                                        &lights[i].Color[0]);
            GLfloat intensityLight = lights[i].Intensity;
            GL->glUniform1f(GL->glGetUniformLocation(programLight.programId(),
                                                      ("lights["+QString::number(i)+"].Intensity").toStdString().c_str()),
                                                        intensityLight);
            GLfloat radiusLight = lights[i].Radius;
            GL->glUniform1f(GL->glGetUniformLocation(programLight.programId(),
                                                      ("lights["+QString::number(i)+"].Radius").toStdString().c_str()),
                                                        radiusLight);
            GLint typeLight = lights[i].TypeLight;
            GL->glUniform1i(GL->glGetUniformLocation(programLight.programId(),
                                                      ("lights["+QString::number(i)+"].TypeLight").toStdString().c_str()),
                                                        typeLight);
            float linear = 0.7f;
            float quadratic = 1.8f;
            GL->glUniform1f(GL->glGetUniformLocation(programLight.programId(),
                                                     ("lights["+QString::number(i)+"].Linear").toStdString().c_str()),
                                                        linear);
            GL->glUniform1f(GL->glGetUniformLocation(programLight.programId(),
                                                     ("lights["+QString::number(i)+"].Quadratic").toStdString().c_str()),
                                                        quadratic);

        }
        GL->glUniform3fv(GL->glGetUniformLocation(programLight.programId(), "viewPos"),1, &camera->position[0]);
        RenderQuad();
    }

    programLight.release();
}

void DeferredRenderer::PassBloom(Camera *camera)
{
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, lightingfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    PassLight(camera);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, bloomfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //QOpenGLFramebufferObject::bindDefault();

    //PassMeshes(camera);¡
    //qInfo() << "Accept: " << acceptBloom;
    if(programBloom.bind())
    {
        programBloom.setUniformValue(programBloom.uniformLocation("cTexture"), 0);
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, lighting);
        //qInfo() << "Accept: " << acceptBloom;
        GLfloat accept = acceptBloom;
        GL->glUniform1f(GL->glGetUniformLocation(programBloom.programId(), "accept"), accept);
        RenderQuad();
    }
    programBloom.release();
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, blurfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    QOpenGLFramebufferObject::bindDefault();
    //PassMeshes(camera);

    if(programBlur.bind())
    {
        programBlur.setUniformValue(programBlur.uniformLocation("image"), 0);
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, bloom);

        GLint horizontal = 0;
        for(int i = 0; i < 2; i++)
        {
            GL->glUniform1i(GL->glGetUniformLocation(programBlur.programId(), "horizontal"), horizontal);
            //qInfo() << "Blur: " << this->intensityBlur;
            GLfloat intensityBlur = this->intensityBlur;
            GL->glUniform1f(GL->glGetUniformLocation(programBlur.programId(), "intensity"), intensityBlur);
            RenderQuad();
            horizontal = 1;
        }
    }
    programBlur.release();
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, finalBloomfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    QOpenGLFramebufferObject::bindDefault();

    if(programFinalBloom.bind())
    {
        programFinalBloom.setUniformValue(programFinalBloom.uniformLocation("scene"), 0);
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, lighting);
        programFinalBloom.setUniformValue(programFinalBloom.uniformLocation("bloomBlur"), 1);
        GL->glActiveTexture(GL_TEXTURE1);
        GL->glBindTexture(GL_TEXTURE_2D, blurHV);

        GLfloat exposure = 1.0f;
        GL->glUniform1f(GL->glGetUniformLocation(programFinalBloom.programId(), "exposure"), exposure);
        RenderQuad();
    }
    programFinalBloom.release();

}

void DeferredRenderer::PassGaussianBlur(Camera* camera)
{
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, lightingfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    PassLight(camera);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    GL->glBindFramebuffer(GL_FRAMEBUFFER, blurfbo);
    GL->glClearDepth(1.0f);
    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //PassMeshes(camera);
    QOpenGLFramebufferObject::bindDefault();
    if(programBlur.bind())
    {
        programBlur.setUniformValue(programBlur.uniformLocation("image"), 0);
        GL->glActiveTexture(GL_TEXTURE0);
        GL->glBindTexture(GL_TEXTURE_2D, lighting);

        GLint horizontal = 0;
        for(int i = 0; i < 2; i++)
        {
            GL->glUniform1i(GL->glGetUniformLocation(programBlur.programId(), "horizontal"), horizontal);
            GLfloat intensityBlur = this->intensityBlur;
            GL->glUniform1f(GL->glGetUniformLocation(programBlur.programId(), "intensity"), intensityBlur);
            RenderQuad();
            horizontal = 1;
        }
    }
    programBlur.release();
}

void DeferredRenderer::RenderQuad()
{
    if (quadVAO == 0)
    {
        GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // Setup plane VAO
        GL->glGenVertexArrays(1, &quadVAO);
        GL->glGenBuffers(1, &quadVBO);
        GL->glBindVertexArray(quadVAO);
        GL->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        GL->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        GL->glEnableVertexAttribArray(0);
        GL->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        GL->glEnableVertexAttribArray(1);
        GL->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    GL->glBindVertexArray(quadVAO);
    GL->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    GL->glBindVertexArray(0);
}
