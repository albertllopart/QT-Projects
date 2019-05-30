#include "deferredrenderer.h"
#include <qopengl.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include "myopenglwidget.h"
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

DeferredRenderer::DeferredRenderer()
{

}

/*void DeferredRenderer::passGrid(Camera *camera)
{
    GLenum drawBuffers = GL_COLOR_ATTACHMENT3;
    glDrawBuffer(drawBuffers);

}*/

/*void DeferredRenderer::LoadGridProgram(const char *path)
{

}*/

void DeferredRenderer::Render(Camera *camera)
{

    GL->glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    GL->glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GL->glClearDepth(1.0f);
    GL->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    RenderQuad();
}

void DeferredRenderer::RenderQuad()
{
    if (quadVAO == 0)
         {
             float quadVertices[] = {
                 // Positions               // texCoords       // Color
                 -1.0f,  1.0f, 0.0f,        0.0f, 1.0f,        1.0, 0.0, 0.0,
                 -1.0f, -1.0f, 0.0f,        0.0f, 0.0f,        0.0, 1.0, 0.0,
                  1.0f,  1.0f, 0.0f,        1.0f, 1.0f,        0.0, 0.0, 0.0,
                  1.0f, -1.0f, 0.0f,        1.0f, 0.0f,        1.0, 1.0, 1.0
             };
             // setup plane VAO
             GL->glGenVertexArrays(1, &quadVAO);
             GL->glGenBuffers(1, &quadVBO);
             GL->glBindVertexArray(quadVAO);
             GL->glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
             GL->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
             GL->glEnableVertexAttribArray(0);
             GL->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
             GL->glEnableVertexAttribArray(1);
             GL->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
             GL->glEnableVertexAttribArray(2);
             GL->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
         }

    GL->glBindVertexArray(quadVAO);
    GL->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    GL->glBindVertexArray(0);
    GL->glBindTexture(GL_TEXTURE_2D, 0);
}
