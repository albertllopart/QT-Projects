#include "shaperenderer.h"

ShapeRenderer::ShapeRenderer(GameObject* gameobject) : Component(gameobject, Type::ComponentRenderer)
{
    name = "Renderer";
    type = ShapeType::Circle;
    strokeStyle = StrokeStyle::SolidLine;
    fillColor = QColor(255,255,255);
    strokeColor= QColor(255,255,255);
    size = 50;
    strokeThickness = 1;
}

void ShapeRenderer::Save(QJsonObject &json) const
{
    json["RendererType"] = type;
    json["StrokeStyle"] = strokeStyle;
    json["FillColorR"] = fillColor.red();
    json["FillColorG"] = fillColor.green();
    json["FillColorB"] = fillColor.blue();
    json["StrokeColorR"] = strokeColor.red();
    json["StrokeColorG"] = strokeColor.green();
    json["StrokeColorB"] = strokeColor.blue();
    json["Size"] = size;
    json["StrokeThickness"] = strokeThickness;
}

void ShapeRenderer::Load(const QJsonObject &json)
{
    type = (ShapeType)json["RendererType"].toInt();
    strokeStyle = (StrokeStyle)json["RendererType"].toInt();
    fillColor = QColor(json["FillColorR"].toInt(),json["FillColorG"].toInt(),json["FillColorB"].toInt());
    strokeColor= QColor(json["StrokeColorR"].toInt(),json["StrokeColorG"].toInt(),json["StrokeColorB"].toInt());
    size = json["Size"].toInt();
    strokeThickness = json["StrokeThickness"].toInt();
}
