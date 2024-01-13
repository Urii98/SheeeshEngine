#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include"ComponentTransform.h"
#include "ComponentAudioListener.h"

class ComponentTransform;




ComponentAudioListener::ComponentAudioListener(GameObject* owner) : Component(owner)
{
	type = ComponentType::AUDIOLISTENER;
	mOwner = owner;

	ListenerGameObject = mOwner;
	listenerID =audioID;
	App->audio->RegisterGameObject(listenerID);
	/*App->audio->SetDefaultListener(listenerID);*/
	
	LOG("AAAAAAA %d", audioID);
}

ComponentAudioListener::~ComponentAudioListener()
{
}

void ComponentAudioListener::Update()
{
	App->audio->SetListenerPos(ListenerGameObject, listenerID);

}

void ComponentAudioListener::PrintInspector()
{

	if (ImGui::CollapsingHeader("Audio Listener"))
	{
		ImGui::Text("AudioClip");
		ImGui::SameLine(ImGui::GetWindowWidth() * 0.65f);
		ImGui::Checkbox("##AudioClip", &activeListener);
		ImGui::SameLine();
		ImGui::Text("Listen");

		if (activeListener)
		{
			App->audio->SetDefaultListener(audioID);
		}
		else if (activeListener == false)
		{
			App->audio->RemoveDefaultListener(audioID);
		}
	}


}