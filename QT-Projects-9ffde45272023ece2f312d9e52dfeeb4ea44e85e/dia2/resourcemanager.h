#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QWidget>
#include <list>
#include <map>

enum ResourceType
{
    RMesh = 0,
    RTexture,
    RMaterial
};

class QListWidget;

class Resource
{
public:
    Resource(ResourceType type) : type(type){}
    virtual ~Resource() {}

    virtual void Draw() {}
    virtual void Update() {}
    virtual void Destroy(){}

    void SetName(const char* name)
    {
        this->name = name;
    }

    const char* GetName() const
    {
        return name.c_str();
    }
    ResourceType GetType() const
    {
        return type;
    }

private:

    std::string name;
    ResourceType type;
};

class ResourceManager: public QWidget
{
    Q_OBJECT

public:
    ResourceManager(QWidget* parent = nullptr);


    void Import(std::string path);
    void AddResource(const Resource* resource);

    int GetCountResources(ResourceType type);

    Resource* GetResource(int i, ResourceType type);
    Resource* GetResourceByName(std::string name, ResourceType type);

    void ImportMesh(std::string path);
    void ImportTexture(std::string path);


private:

    std::list<Resource*> resources;
    QListWidget* resourcesList = nullptr;





};

#endif // RESOURCEMANAGER_H
