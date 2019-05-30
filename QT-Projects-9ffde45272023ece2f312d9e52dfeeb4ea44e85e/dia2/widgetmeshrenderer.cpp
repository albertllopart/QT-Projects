#include "widgetmeshrenderer.h"
#include "ui_widgetmeshrenderer.h"
#include "meshrenderer.h"
#include "scene.h"
#include "resourcemanager.h"
#include <QDebug>
#include "mesh.h"
#include "submesh.h"

WidgetMeshRenderer::WidgetMeshRenderer(Scene* scene, MeshRenderer* mesh, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMeshRenderer)
{
    ui->setupUi(this);

    this->scene = scene;
    this->meshRenderer = mesh;

    bool hasMesh = false;
    int indexToSelect = 0;
    ui->ComboMesh->addItem("No Mesh...");
    for (int i = 0; i < scene->resourceManager->GetCountResources(ResourceType::RMesh); i++)
    {
        Resource* r = scene->resourceManager->GetResource(i, ResourceType::RMesh);
        ui->ComboMesh->addItem(r->GetName());
        if (this->meshRenderer->GetMesh() != nullptr && r->GetName() == this->meshRenderer->GetMesh()->GetName())
        {
            indexToSelect = i + 1;
            hasMesh = true;
        }
    }
    if(hasMesh)
    {
        ui->ComboMesh->setCurrentIndex(indexToSelect);
        if (ui->Textures->itemAt(0) != nullptr)
        {
            ChangeMesh(ui->Textures);
        }
        if(mesh == nullptr)
        {
            ConnectSignalsSlots();
            return;
        }
        AddTexturesLayout(this->meshRenderer->GetMesh());
    }

    //ui->ComboMaterial->addItem("No Texture...");

    ConnectSignalsSlots();
}

WidgetMeshRenderer::~WidgetMeshRenderer()
{
    delete ui;
}

void WidgetMeshRenderer::ConnectSignalsSlots()
{
    connect(ui->ComboMesh,               SIGNAL(currentIndexChanged(int)), this,    SLOT(UpdateMeshRenderer()));
    //connect(ui->ComboMaterial,           SIGNAL(currentIndexChanged(int)), this,    SLOT(UpdateTexture()));
}

void WidgetMeshRenderer::UpdateMeshRenderer()
{
    Mesh* mesh = (Mesh*)scene->resourceManager->GetResource(ui->ComboMesh->currentIndex() - 1, ResourceType::RMesh);
    if(mesh != nullptr)
        meshRenderer->SetMesh(mesh);


    if (ui->Textures->itemAt(0) != nullptr)
    {
        ChangeMesh(ui->Textures);
    }

    if(mesh == nullptr)
    {
        emit InspectorUpdate();
        return;
    }
    AddTexturesLayout(mesh);

    emit InspectorUpdate();
}

void WidgetMeshRenderer::AddTexturesLayout(Mesh* mesh)
{
    foreach (SubMesh* sub, mesh->meshes)
    {
        qInfo() << "UPDATEEEEEEE";
        QHBoxLayout* box = new QHBoxLayout();

        const char* name = sub->meshName.c_str();
        QLabel* la = new QLabel(QString(name));
        la->setStyleSheet("font-style: normal");

        QComboBox* combo = new QComboBox();
        combo->addItem("Select Texture...");
        for (int i = 0; i < scene->resourceManager->GetCountResources(ResourceType::RTexture); i++)
        {
            Resource* r = scene->resourceManager->GetResource(i, ResourceType::RTexture);
            combo->addItem(r->GetName());
        }
        connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateTexture()));
        box->addWidget(la);
        box->addWidget(combo);
        ui->Textures->addLayout(box);
    }
}

void WidgetMeshRenderer::ChangeMesh(QLayout* layout)
{
    QLayoutItem* child;
    while (layout->count() != 0)
    {
        child = layout->takeAt(0);
        if (child->layout() != nullptr)
        {
            ChangeMesh(child->layout());
        }
        else if (child->widget() != nullptr)
        {
            delete child->widget();
        }
        delete child;
    }
}

void WidgetMeshRenderer::UpdateTexture()
{
    //mesh->SetMaterial((Material*)scene->resourceManager->GetResource(ui->ComboMesh->currentIndex() - 1, ResourceType::RMaterial));
    emit InspectorUpdate();
}






