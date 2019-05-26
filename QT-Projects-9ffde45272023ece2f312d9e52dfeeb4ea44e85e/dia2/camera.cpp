#include "camera.h"
#include <QtMath>

Camera::Camera()
{
    worldMatrix = QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    viewMatrix = QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    projectionMatrix = QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
}

void Camera::prepareMatrices()
{
    worldMatrix.setToIdentity();
    worldMatrix.translate(position);
    worldMatrix.rotate(yaw, QVector3D(0.0, 1.0, 0.0));
    worldMatrix.rotate(pitch, QVector3D(1.0, 0.0, 0.0));

    //do not confuse this worldMatrix with the worldMatrix (or modelMatrix) of entities
    //this camera worldMatrix transforms from viewspace (camera's local space) to worldspace

    viewMatrix = worldMatrix.inverted();

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fovy, float(viewportWidth) / viewportHeight, znear, zfar);
}

QVector4D Camera::getLeftRightBottonTop()
{
    const float aspectRatio = float(viewportWidth) / viewportHeight;
    const float alpha = qDegreesToRadians(fovy * 0.5);
    const float top = znear * qTan(alpha);
    const float bottom = -top;
    const float right = top * aspectRatio;
    const float left = -right;

    return QVector4D(left, right, bottom, top);
}

QVector3D Camera::screenPointToWorldRay(int x, int y)
{
    QVector4D lrbt = getLeftRightBottonTop();
    const float l = lrbt.x();
    const float r = lrbt.y();
    const float b = lrbt.z();
    const float t = lrbt.w(); //left, right, botton and top define the corners of near plane in viewspace

    const float rayX = l + (r - l) * x / viewportWidth;
    const float rayY = b + (t - b) * (viewportHeight - y - 1) / viewportHeight; //rayX and rayY obtained by interpolating between the corners of the near plane
    const float rayZ = -znear;

    QVector3D rayViewspace = QVector3D(rayX, rayY, rayZ);

    prepareMatrices();
    QVector3D rayWorldspace = QVector3D(worldMatrix * QVector4D(rayViewspace, 0.0));

    return rayWorldspace;
}
