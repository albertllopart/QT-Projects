#include "widgetmeshrenderer.h"
#include "ui_widgetmeshrenderer.h"
#include "meshrenderer.h"
#include "scene.h"
#include "resourcemanager.h"

WidgetMeshRenderer::WidgetMeshRenderer(Scene* scene, MeshRenderer* mesh, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMeshRenderer)
{
    ui->setupUi(this);

    this->scene = scene;
    this->mesh = mesh;

    ui->ComboMesh->addItem("No Mesh...");
    for (int i = 0; i < scene->resourceManager->GetCountResources(ResourceType::RMesh); i++)
    {
        ui->ComboMesh->addItem(scene->resourceManager->GetResource(i, ResourceType::RMesh)->GetName());
    }
    ui->ComboMaterial->addItem("No Material...");
    for (int i = 0; i < scene->resourceManager->GetCountResources(ResourceType::RMaterial); i++)
    {
        ui->ComboMaterial->addItem(scene->resourceManager->GetResource(i, ResourceType::RMaterial)->GetName());
    }

    ConnectSignalsSlots();
}

WidgetMeshRenderer::~WidgetMeshRenderer()
{
    delete ui;
}

void WidgetMeshRenderer::ConnectSignalsSlots()
{
    connect(ui->ComboMesh,               SIGNAL(currentIndexChanged(int)), this,    SLOT(UpdateMeshRenderer()));
    connect(ui->ComboMaterial,           SIGNAL(valueChanged(int)),        this,    SLOT(UpdateMaterial()));
}

void WidgetMeshRenderer::UpdateMeshRenderer()
{
    mesh->SetMesh((Mesh*)scene->resourceManager->GetResource(ui->ComboMesh->currentIndex() - 1, ResourceType::RMesh));
    emit InspectorUpdate();
}

void WidgetMeshRenderer::UpdateMaterial()
{
    mesh->SetMaterial((Material*)scene->resourceManager->GetResource(ui->ComboMesh->currentIndex() - 1, ResourceType::RMaterial));
    emit InspectorUpdate();
}






