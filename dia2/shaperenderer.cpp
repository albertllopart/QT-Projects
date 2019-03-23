#include "shaperenderer.h"

ShapeRenderer::ShapeRenderer(GameObject* gameobject) : Component(gameobject, Type::ComponentRenderer)
{
    name = "Renderer";
    fillColor = QColor(255,255,255);
    strokeColor= QColor(0,0,0);
    size = 32;
}
