
#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
//#include "MeshLoader.h"
#include "AudioEvent.h"
#include "ComponentTransform.h"

#include <iostream>
#include <string>
#include <vector>

class AudioEvent;


class ComponentAudioSource : public Component
{
public:
	
	ComponentAudioSource(GameObject* gameObject);
	~ComponentAudioSource();

	void Update() override;

	GameObject* SourceGameObject;
	uint sourceID;
	ComponentTransform* transform;
	std::vector<std::string> events = App->audio->wwiseData.events;


	void PrintInspector();

	float volume;
	bool isPlaying = false;
	bool nothingSelected = false;
	std::string audioClip;
};