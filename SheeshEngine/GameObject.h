#pragma once
#include "Module.h"
#include <vector>
#include <string>


enum class ComponentType;
enum class GeometryType;
class Component;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class ComponentCamera;
class ComponentAudioListener;
class ComponentAudioSource;
class ComponentReverbAudio;
class GameObject
{
public:

	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void AddComponent(Component* component);
	void Update();
	GameObject* GetParent();
	bool SetNewParent(GameObject* newParent);
	bool GameObject::SetAsChildOf(GameObject* gameObject);
	void AttachChild(GameObject* child);
	void PrintInspector();
	bool CheckChildOf(GameObject* parent);
	void DeleteChild(GameObject* child);


	ComponentMesh* GetMeshComponent();

	ComponentTransform* GetTransformComponent();

	ComponentMaterial* GetComponentTexture();

	ComponentCamera* GetComponentCamera();

	ComponentAudioListener* GetComponentAudio();

	ComponentAudioSource* GetComponentAudioSource();

	ComponentReverbAudio* GetComponentReverbAudio();


	void SetPendingToDelete(bool deleteGO) { isTimetoDelete = deleteGO; };

	bool isTimetoDelete;
	bool isActive;
	std::string name;
	int componentNum;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	ComponentTransform* transform;
	GeometryType Stype;

};