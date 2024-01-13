#pragma once

#include "Component.h"
#include "MathGeoLib/include/Geometry/AABB.h"
#include <string>


class IndexBuffer;
class VertexBuffer;
class GameObject;
class ComponentTransform;
class Component;

class ComponentReverbAudio : public Component
{
public:
	ComponentReverbAudio(GameObject* own);

	~ComponentReverbAudio();

	void ResizeReverbZone();

	void Update() override;

	void PrintInspector() override;

	GameObject* owner;

	ComponentTransform* transform;

	inline AABB GetReverbZoneAABB() const { return reverbBoxZone; }
	inline std::string GetReverbBusName() const { return busReverb; }

	void CompileBuffers();
	void Draw();

private:
	
	AABB reverbBoxZone;
	std::string busReverb;

	
	IndexBuffer* ebo;
	VertexBuffer* vbo;

	float3 dimensions;
}; 
