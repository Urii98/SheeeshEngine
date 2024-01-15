#pragma once
enum class ComponentType
{
    NONE,
    TRANSFORM,
    MESH,
    MATERIAL,
    CAMERA,
    AUDIOLISTENER,
    AUDIOSOURCE

};

class GameObject;

class Component {

public:
    Component(GameObject* owner);
    Component(GameObject* owner, int id);
    virtual ~Component();

    virtual void PrintInspector();
    virtual void Update();

    void EnableComponent();
    void DisableComponent();

    ComponentType type;
    bool isActive;

    GameObject* mOwner;
    int audioID;

};