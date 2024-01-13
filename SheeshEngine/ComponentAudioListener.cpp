#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentAudioListener.h"

ComponentAudioListener::ComponentAudioListener() : Component(nullptr)
{
	type = ComponentType::AUDIOLISTENER;
}


ComponentAudioListener::ComponentAudioListener(GameObject* owner) : Component(owner)
{
	type = ComponentType::AUDIOLISTENER;
	mOwner = owner;
	

	LOG("AAAAAAA %d", audioID);
}

ComponentAudioListener::~ComponentAudioListener()
{
}

void ComponentAudioListener::Update()
{
}

void ComponentAudioListener::PrintInspector()
{
	//if (ImGui::CollapsingHeader("Audio Listener"))
	//{

	//	//ImGui::TextColored(ImVec4(255, 255, 0, 255), "Enabled: "); ImGui::SameLine(); ImGui::Checkbox("##audioListenerEnabled", &enabled);

	//	ImGui::Spacing();
	//	ImGui::Spacing();

	//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.5f, 0.5f, 1.0f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));

	//	if (ImGui::Button("Remove Component ##listener", ImVec2(ImGui::GetWindowSize().x, 20.0f)))
	//		//go->RemoveComponent(this);

	//	ImGui::PopStyleColor(3);

	//	ImGui::Spacing();

	//}


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