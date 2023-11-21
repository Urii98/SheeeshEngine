#pragma once
#include "Module.h"
#include "Globals.h"
#include "ComponentCamera.h"
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/float4x4.h"

#include "glmath.h"
class ComponentCamera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look();
	void LookAt(const float3& Spot);
	void Move(const float3& Movement);
	float* GetViewMatrix();
	void FocusCameraToSelectedObject();
	void RotationAroundCamera();
	void OrbitSelectedObject(float dt);
	float3 RotateVector(const float3& u, float angle, const float3& v);

	bool SaveConfig(JsonParser& node) const;
	bool LoadConfig(JsonParser& node);
private:

	void CalculateViewMatrix();
	

public:

	ComponentCamera* sceneCamera;
	float mouseSens = 0.50f;
	float3 X, Y, Z, Position, Reference;

private:

	mat4x4 ViewMatrix;
	
};