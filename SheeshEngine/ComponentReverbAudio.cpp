#include "ComponentReverbAudio.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleAudio.h"

ComponentReverbAudio::ComponentReverbAudio(GameObject* own) :  Component(own)
{
	owner = own;
	type = ComponentType::AUDIOREBERV;

	// Register this audio source

	App->audio->RegisterGameObject(audioID);

	//if (!owner->CheckAudioRegister())
	//{
	//	AkGameObjectID cameraID = owner->GetUUID();
	//	a->RegisterGameObject(cameraID);
	//	owner->SetAudioRegister(true);
	//}
}

ComponentReverbAudio::~ComponentReverbAudio()
{
}

void ComponentReverbAudio::Update()
{

	App->audio->SetListenerPos(owner, audioID);
	//DEBUG_LOG("Source: x %f, y %f, z %f", position.x, position.y, position.z);

		
}

void ComponentReverbAudio::PrintInspector()
{
	if (ImGui::CollapsingHeader("Audio Reverb Zone"))
	{

	}
}