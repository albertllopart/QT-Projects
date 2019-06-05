#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>

class Camera;

struct LightScene {
    QVector3D Position;
    QVector3D Color;
    float Intensity = 1.0;
    float Radius = 0;
    int TypeLight = 0; // 0 == Directional | 1 == PointLight
};

class DeferredRenderer
{
public:

    DeferredRenderer();

    void InitDeferredRenderer();
    void DeleteBuffers();
    void Resize(int width,int height);

    void Render(Camera* camera);
    void PassMeshes(Camera* camera);
    void PassGrid(Camera* camera);
    void PassLight(Camera* camera);
    void PassLight2(Camera* camera);
    void PassBloom(Camera* camera);
    void PassGaussianBlur(Camera* camera);
    void RenderQuad();
    void DrawGrid();


public:

    int renderView = 0;
    unsigned int fbo;
    unsigned int colorTexture;
    unsigned int normalTexture;
    unsigned int depthTexture;
    unsigned int positionTexture;

    // Bloom
    //unsigned int colorTexture;

    // Gaussian Blur
    //unsigned int blurfbo;
    //unsigned int blur;

    QOpenGLShaderProgram program;
    QOpenGLShaderProgram programLight;
    QOpenGLShaderProgram programBloom;
    QOpenGLShaderProgram programBlur;
    //QOpenGLShaderProgram programGrid;
    unsigned int attachments[3];

    unsigned int quadVAO = 0;
    unsigned int quadVBO;

private:
    QList<LightScene> lights;

};

#endif // DEFERREDRENDERER_H
