#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

class Camera;

class DeferredRenderer
{
public:

    DeferredRenderer();

    //void passGrid(Camera* camera);

    /*QOpenGLShaderProgram gridProgram;
    void LoadGridProgram(const char* path);*/

    void Render(Camera* camera);
    void RenderQuad();


public:

    unsigned int gBuffer;


    unsigned int quadVAO = 0;
    unsigned int quadVBO;

};

#endif // DEFERREDRENDERER_H
