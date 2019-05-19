#ifndef CAMERA_H
#define CAMERA_H

#include <qvector4d.h>
#include <qvector3d.h>
#include <qvector2d.h>
#include <qmatrix4x4.h>

class Camera
{
public:

    Camera();

    QVector4D getLeftRightBottonTop();

    QVector3D screenPointToWorldRay(int x, int y);
    QVector3D screenDisplacementToWorldVector(int x0, int y0, int x1, int y1);
    QVector2D worldToScreenPoint(const QVector3D &p);

    // create the matrices
    void prepareMatrices();

    // viewport
    int viewportWidth = 128;
    int viewportHeight = 128;

    // projection
    float fovy = 1;
    float znear = 1;
    float zfar = 300;

    // world navigation
    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    // speed
    float speed = 1;

    // derived matrices
    QMatrix4x4 worldMatrix; // from camera space to world space
    QMatrix4x4 viewMatrix; // from world space to camera space
    QMatrix4x4 projectionMatrix; // from view space to clip space
};

#endif // CAMERA_H