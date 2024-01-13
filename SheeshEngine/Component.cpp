#include "Component.h"

int audioCounter = 0;



Component::Component(GameObject* owner)
{
    type = ComponentType::NONE;

    isActive = false;

    this->mOwner = owner;

     
    this->audioID = audioCounter;
    
    audioCounter++;

}


Component::~Component()
{

}

void Component::Update()
{

}

void Component::PrintInspector() {}

void Component::EnableComponent() {}

void Component::DisableComponent() {}