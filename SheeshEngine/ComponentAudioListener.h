#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
//#include "ModuleFilesManager.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ComponentAudioListener : public Component
{
public:
	ComponentAudioListener();
	ComponentAudioListener(GameObject* owner);
	~ComponentAudioListener();

	void Update() override;
	ComponentTransform* transform;
	bool activeListener;
	GameObject* ListenerGameObject;
	unsigned int listenerID;
	void PrintInspector();

};