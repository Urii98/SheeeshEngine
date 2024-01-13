#include "ComponentReverbAudio.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleAudio.h"
#include "ComponentTransform.h"
#include "Glew/include/glew.h"

ComponentReverbAudio::ComponentReverbAudio(GameObject* own) :  Component(own)
{
	owner = own;
	type = ComponentType::AUDIOREBERV;
	vbo = nullptr;
	ebo = nullptr;
	// Register this audio source
	transform = owner->GetTransformComponent();
	App->audio->RegisterGameObject(audioID);

	//if (!owner->CheckAudioRegister())
	//{
	//	AkGameObjectID cameraID = owner->GetUUID();
	//	a->RegisterGameObject(cameraID);
	//	owner->SetAudioRegister(true);
	//}

	CompileBuffers();
}

ComponentReverbAudio::~ComponentReverbAudio()
{
	App->audio->DeleteReverbZone(this);
	RELEASE(vbo);
	RELEASE(ebo);
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

void ComponentReverbAudio::CompileBuffers()
{
	// Configure buffers
	float3 corners[8];
	reverbBoxZone.GetCornerPoints(corners);
	unsigned int indices[24] =
	{
		0,1,
		1,3,
		3,2,
		2,0,

		1,5,
		4,6,
		7,3,

		6,7,
		6,2,

		7,5,
		4,5,

		4,0
	};

	if (vbo)
	{
		vbo->Unbind();
		RELEASE(vbo);
	}
	ebo = new IndexBuffer(indices, 24);
	vbo = new VertexBuffer(corners, sizeof(float3) * 8);
	ebo->Unbind();
	vbo->Unbind();
}

void ComponentReverbAudio::Draw()
{
	glPushMatrix();

	glMultMatrixf(transform->getGlobalMatrix().Transposed().ptr());
	glEnableClientState(GL_VERTEX_ARRAY);
	vbo->Bind();
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	ebo->Bind();
	glLineWidth(2.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glDrawElements(GL_LINES, ebo->GetSize(), GL_UNSIGNED_INT, NULL);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(1.0f);
	vbo->Unbind();
	ebo->Unbind();
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}
