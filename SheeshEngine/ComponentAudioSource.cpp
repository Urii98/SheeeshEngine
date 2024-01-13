#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentAudioSource.h"


#include <iostream>
#include <string>
#include <vector>



ComponentAudioSource::ComponentAudioSource(GameObject* owner) : Component(owner)
{
	SourceGameObject = owner;
	sourceID = audioID;

	events = App->audio->wwiseData.events;
	type = ComponentType::AUDIOSOURCE;
	App->audio->RegisterGameObject(sourceID);

	audioClip = events[0];
	App->audio->PostEvent(audioClip.c_str(), sourceID);
	isPlaying = true;
	LOG("AAAAAAA %d", sourceID);
}

ComponentAudioSource::~ComponentAudioSource()
{
	App->audio->StopEvent(audioClip.c_str(), sourceID);
	isPlaying = false;
	App->audio->UnregisterGameObject(sourceID);
}

bool ComponentAudioSource::Update(float dt)
{
	//float3 position = transform->getPosition();
	//AkSoundPosition audioSourcePos;
	//audioSourcePos.SetPosition(position.x, position.y, position.z);
	//float3 orientation = transform->getRotation();
	////audioSourcePos.SetOrientation({orientation.x, orientation.y, orientation.z}, { orientation.x, orientation.y, orientation.z });
	/*audioSourcePos.SetOrientation({ 0, 0, -1 }, { 0,1,0 });*/
	App->audio->SetListenerPos(mOwner,sourceID);
	//DEBUG_LOG("Source: x %f, y %f, z %f", position.x, position.y, position.z);
	return true;
}

void ComponentAudioSource::PrintInspector()
{

	if (ImGui::CollapsingHeader("Audio Source"))
	{
		ImGui::Text("AudioClip");
		ImGui::SameLine();
		if (ImGui::BeginCombo("##AudioClip", audioClip.c_str()))
		{
			if (ImGui::Selectable("None"))
			{
				audioClip = "None";
				nothingSelected = true;
			}

			for (int i = 0; i < events.size(); i++)
			{
				if (ImGui::Selectable(events[i].c_str()))
				{
					nothingSelected = false;
					audioClip = events[i];

				}
			}

			ImGui::EndCombo();
		}

		ImGui::Text("Volume (Doesn't work)");
		ImGui::SameLine();
		if (ImGui::SliderFloat("##Volume", &volume, 0.0f, 100.0f))
		{
			/*App->audio->SetRTPCValue("Volume", volume, sourceID);*/

			AK::SoundEngine::SetRTPCValue("Volume", volume, sourceID);
		}
		if (ImGui::Button("Play"))
		{
			if (isPlaying == false || nothingSelected == false)
			{
				App->audio->PostEvent(audioClip.c_str(), sourceID);
				isPlaying = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
		{
			App->audio->PauseEvent(audioClip.c_str(), sourceID);
		}
		ImGui::SameLine();
		if (ImGui::Button("Resume"))
		{
			App->audio->ResumeEvent(audioClip.c_str(), sourceID);
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			App->audio->StopEvent(audioClip.c_str(), sourceID);
			isPlaying = false;
		}

	}



}
