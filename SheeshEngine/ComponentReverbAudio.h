#pragma once

#include "Component.h"


class GameObject;
class Component;

class ComponentReverbAudio : public Component
{
public:
	ComponentReverbAudio(GameObject* own);

	~ComponentReverbAudio();

	void Update() override;

	void PrintInspector() override;

	GameObject* owner;

	

private:
	
}; 
