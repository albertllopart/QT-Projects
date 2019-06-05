#include "widgetmeshrenderer.h"
#include "ui_widgetmeshrenderer.h"
#include "meshrenderer.h"
#include "scene.h"
#include "resourcemanager.h"
#include <QDebug>
#include "mesh.h"
#include "submesh.h"
#include "texture.h"

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
        if (this->meshRenderer->GetMesh() != nullptr)
        {
            std::string name1 = r->GetName();
            std::string name2 = this->meshRenderer->GetMesh()->GetName();
            if(name1 == name2)
            {
                indexToSelect = i + 1;
                hasMesh = true;
            }
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
    Mesh* mesh = (Mesh*)scene->resourceManager->GetResourceObject(ui->ComboMesh->currentIndex() - 1, ResourceType::RMesh);
    if(mesh != nullptr)
    {
        qInfo() << "okey........................";
        meshRenderer->SetMesh(mesh);
    }
    else
    {
        meshRenderer->SetMesh(nullptr);
    }


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
    int index = 0;
    bool hasMesh = false;
    int indexToSelect = 0;
    foreach (SubMesh* sub, mesh->meshes)
    {
        qInfo() << "UPDATEEEEEEE";
        QHBoxLayout* box = new QHBoxLayout();

        const char* name = sub->meshName.c_str();
        QLabel* la = new QLabel(QString(name));
        la->setStyleSheet("font-style: normal");

        QComboBox* combo = new QComboBox();
        combo->setObjectName(QString::number(index));
        combo->addItem("Select Texture...");
        for (int i = 0; i < scene->resourceManager->GetCountResources(ResourceType::RTexture); i++)
        {
            Resource* r = scene->resourceManager->GetResource(i, ResourceType::RTexture);
            combo->addItem(r->GetName());
            std::string name1 = r->GetName();
            std::string name2 = sub->texture->GetName();
            if(name1 == name2)
            {
                hasMesh = true;
                indexToSelect = i + 1;
            }
        }
        if(hasMesh)
            combo->setCurrentIndex(indexToSelect);
        std::string temp = name;
        box->addWidget(la);
        box->addWidget(combo);
        connect(combo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(UpdateTexture(const QString&)));
        ui->Textures->addLayout(box);
        index++;
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

void WidgetMeshRenderer::UpdateTexture(const QString& nameSubmesh)
{
    //qInfo() << "Texture NULL" <<sender();
    //qInfo() << "Texture NULL" << sender()->objectName().toStdString();
    //qInfo() << "Texture NULL" <<;

    int index = std::stoi(sender()->objectName().toStdString());
    Texture* newTexture = (Texture*)scene->resourceManager->GetResource(nameSubmesh.toStdString());
    if(newTexture == nullptr)
    {
        qInfo() << "Texture NULL";
        meshRenderer->GetMesh()->meshes[index]->texture = (Texture*)scene->resourceManager->GetResource(0, ResourceType::RTexture);
    }
    else
    {
        meshRenderer->GetMesh()->meshes[index]->texture = newTexture;
    }
    //meshRenderer->SetMaterial((Material*)scene->resourceManager->GetResource(ui->ComboMesh->currentIndex() - 1, ResourceType::RMaterial));
    emit InspectorUpdate();
}






