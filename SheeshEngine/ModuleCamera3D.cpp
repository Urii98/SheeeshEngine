﻿#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "MathGeoLib/include/Math/float3.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Camera3D";

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	sceneCamera = new ComponentCamera();
	sceneCamera->FrustumCam.pos = float3(0, 0, 0);
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	delete sceneCamera;

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	int wheel = -App->input->GetMouseZ();
	float speed = 8.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * 2 * dt;

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) sceneCamera->FrustumCam.pos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) sceneCamera->FrustumCam.pos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) sceneCamera->FrustumCam.pos += sceneCamera->FrustumCam.front * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) sceneCamera->FrustumCam.pos -= sceneCamera->FrustumCam.front * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) sceneCamera->FrustumCam.pos -= sceneCamera->FrustumCam.WorldRight() * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) sceneCamera->FrustumCam.pos += sceneCamera->FrustumCam.WorldRight() * speed;

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) RotationAroundCamera();

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		if (App->hierarchy->objSelected != nullptr) {
			float3 target = App->hierarchy->objSelected->transform->getPosition();
			sceneCamera->LookAt(target);

			float TargetDist = sceneCamera->FrustumCam.pos.Distance(target);

			RotationAroundCamera();

			sceneCamera->FrustumCam.pos = target + (sceneCamera->FrustumCam.front * -TargetDist);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		if (App->hierarchy->objSelected != nullptr) {
			float3 target = App->hierarchy->objSelected->transform->getPosition();

			sceneCamera->LookAt(target);
		}
	}

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look()
{

	Z = (Position - Reference).Normalized();
	X = (float3(0.0f, 1.0f, 0.0f).Cross(Z)).Normalized();
	Y = Z.Cross(X);

	this->Position += Z * 0.05f;

	CalculateViewMatrix();	
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const float3& Spot)
{
	Reference = Spot;

	//Cuando se hace un Load, por algun motivo al normalizar los ejes los convierte todos en 0,1,0. Se pierden todos los datos.
	//Se guarda bien la posicion pero debido a que hace mal la normalizacion (creo), la rotacion no se guarda
	Z = (Position - Reference).Normalized();
	X = (float3(0.0f, 1.0f, 0.0f).Cross(Z)).Normalized();
	Y = Z.Cross(X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3& Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return ViewMatrix.M;
}

void ModuleCamera3D::FocusCameraToSelectedObject()
{

	float3 focusObjectPosition;
	//Get the GameObject selected in hierarchy
	if (App->hierarchy->objSelected != nullptr)
	{
		focusObjectPosition = App->hierarchy->objSelected->transform->getPosition();
		LookAt(focusObjectPosition);
	}

}

void ModuleCamera3D::OrbitSelectedObject(float dt)
{
	float3 pivot = float3(0, 0, 0);
	GameObject* gameObject = App->hierarchy->objSelected;

	float3 posGO = { 0, 0, 0 };

	if (gameObject != nullptr)posGO = gameObject->transform->getPosition();

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();
		float Sensitivity = 0.5f * dt;

		if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
		{

			if (gameObject != nullptr)
			{
				pivot = float3(posGO.x, posGO.y, posGO.z);
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}

		Position -= pivot;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			X = RotateVector(X, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Y = RotateVector(Y, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Z = RotateVector(Z, DeltaX, float3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Y = RotateVector(Y, DeltaY, X);
			Z = RotateVector(Z, DeltaY, X);

			if (Y.y < 0.0f)
			{
				Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = Cross(Z, X);

			}
		}
		Position = pivot + Z * Length(Position);
		Reference = pivot;

	}

}

void ModuleCamera3D::RotationAroundCamera()
{
	int dx = -App->input->GetMouseXMotion();
	int dy = -App->input->GetMouseYMotion();

	Quat dir;
	sceneCamera->FrustumCam.WorldMatrix().Decompose(float3(), dir, float3());

	if (dy != 0) {
		float DeltaY = (float)dy * mouseSens;

		Quat Y = Quat::identity;
		Y.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DeltaY * DEGTORAD);

		dir = dir * Y;
	}

	if (dx != 0) {
		float DeltaX = (float)dx * mouseSens;

		Quat X = Quat::identity;
		X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);

		dir = X * dir;
	}

	float4x4 matrix = sceneCamera->FrustumCam.WorldMatrix();
	matrix.SetRotatePart(dir.Normalized());
	sceneCamera->FrustumCam.SetWorldMatrix(matrix.Float3x4Part());
}

float3 ModuleCamera3D::RotateVector(const float3& u, float angle, const float3& v)
{
	// Crear un cuaterni�n de rotaci�n a partir del eje y el �ngulo
	Quat rotationQuat = Quat::RotateAxisAngle(v, angle);

	// Aplicar la rotaci�n al vector
	return rotationQuat * u;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	//todo: USE MATHGEOLIB here BEFORE 1st delivery! (TIP: Use MathGeoLib/Geometry/Frustum.h, view and projection matrices are managed internally.)
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -(X.Dot(Position)), -(Y.Dot(Position)), -(Z.Dot(Position)), 1.0f);
	
}

bool ModuleCamera3D::SaveConfig(JsonParser& node) const
{
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "X.x", X.x);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "X.y", X.y);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "X.z", X.z);

	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Y.x", Y.x);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Y.y", Y.y);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Y.z", Y.z);

	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Z.x", Z.x);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Z.y", Z.y);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Z.z", Z.z);

	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Reference.x", Reference.x);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Reference.y", Reference.y);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Reference.z", Reference.z);

	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Position.x", Position.x);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Position.y", Position.y);
	node.SetNewJsonNumber(node.ValueToObject(node.GetRootValue()), "Position.z", Position.z);

	return true;
}

bool ModuleCamera3D::LoadConfig(JsonParser& node)
{

	X.x = node.JsonValToNumber("X.x");
	X.y = node.JsonValToNumber("X.y");
	X.z = node.JsonValToNumber("X.z");

	Y.x = node.JsonValToNumber("Y.x");
	Y.y = node.JsonValToNumber("Y.y");
	Y.z = node.JsonValToNumber("Y.z");

	Z.x = node.JsonValToNumber("Z.x");
	Z.y = node.JsonValToNumber("Z.y");
	Z.z = node.JsonValToNumber("Z.z");

	Position.x = node.JsonValToNumber("Position.x");
	Position.y = node.JsonValToNumber("Position.y");
	Position.z = node.JsonValToNumber("Position.z");

	Reference.x =node.JsonValToNumber("Reference.x");
	Reference.y =node.JsonValToNumber("Reference.y");
	Reference.z =node.JsonValToNumber("Reference.z");

	LookAt(Reference);

	return true;
}