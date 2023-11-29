#include "ModuleScene.h"
#include "GameObject.h"
#include "Application.h"


ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled) 
{
    name = "Scene";
}

ModuleScene::~ModuleScene() 
{
}

bool ModuleScene::Init()
{

    jsonFile.FileToValue("scene.json");
    return false;
}

bool ModuleScene::Start() {
    
    root = new GameObject(nullptr);
    root->name = ("Scene"); 



    //Load Baker House
    App->assimpMeshes->LoadMeshFromFile("Assets/Models/BakerHouse.fbx");
   

    return true;
}


update_status ModuleScene::PreUpdate(float dt) {
    
    return UPDATE_CONTINUE;
}

update_status ModuleScene::Update(float dt) {
    
    root->Update();
    UpdateGameObjects();
    return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate(float dt) {
    
    return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() {
    
    LOG("Scene Cleanup")
    delete root;
    return true;
}

GameObject* ModuleScene::CreateGameObject(GameObject* parent)
{
    GameObject* newGameObject = new GameObject(parent);



    return newGameObject;

}

bool ModuleScene::SaveScene()
{
	LOG("Saving scene");

	rootFile = jsonFile.GetRootValue();

	JsonParser scene = jsonFile.SetChild(rootFile, "GameObjects");

	SaveGameObjects(root, scene.SetChild(scene.GetRootValue(), root->name.c_str()));

	jsonFile.SerializeFile(rootFile, "scene.json");
	saveSceneRequest = false;
	return true;
}


void ModuleScene::SaveGameObjects(GameObject* parentGO, JsonParser& node) {
    std::string num;
    JsonParser& child = node;

    node.SetNewJsonString(node.ValueToObject(node.GetRootValue()), "name", parentGO->name.c_str());
    node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "active", parentGO->isActive);
    node.SetNewJsonBool(node.ValueToObject(node.GetRootValue()), "pendingToDelete", parentGO->isTimetoDelete);

    JsonParser& components = node.SetChild(node.GetRootValue(), "components");
    for (size_t i = 0; i < parentGO->mComponents.size(); i++)
    {
        components.SetNewJsonBool(components.ValueToObject(components.GetRootValue()), "pendingToDelete", parentGO->isTimetoDelete);
        
    }

    for (size_t i = 0; i <= parentGO->mChildren.size(); i++)
    {

        num = "Child " + std::to_string(i);

        if (parentGO->mChildren.size() > i) {
            SaveGameObjects(parentGO->mChildren[i], child.SetChild(child.GetRootValue(), num.c_str()));
        }
    }
}

bool ModuleScene::LoadScene()
{
	return false;
}

void ModuleScene::UpdateGameObjects()
{
    

    if (saveSceneRequest)SaveScene();
}

