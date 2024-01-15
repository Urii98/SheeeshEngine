
#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
//#include "MeshLoader.h"
#include "AudioEvent.h"

#include <iostream>
#include <string>
#include <vector>

class AudioEvent;

class ComponentAudioSource : public Component
{
public:
	
	ComponentAudioSource(GameObject* gameObject);
	~ComponentAudioSource();

	GameObject* SourceGameObject;
	uint sourceID;

	std::vector<std::string> events;

	void Update() override;
	void PrintInspector();

	float volume;
	bool isPlaying = false;
	bool nothingSelected = false;
	std::string audioClip;
};