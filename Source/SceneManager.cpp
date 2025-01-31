#include "SceneManager.h"
#include "iostream"

std::unordered_map<std::string, Scene*> SceneManager::Scenes;
std::unordered_map<std::string, std::any> SceneManager::SharedData;
Scene* SceneManager::currentScene = nullptr;


void SceneManager::AddScene(Scene* scene, const std::string& sceneName) {
	if (Scenes.find(sceneName) == Scenes.end()) {
		Scenes.insert(std::make_pair(sceneName, scene));
	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' already exists!\n";
	}

}

void SceneManager::SetScene(const std::string& sceneName) {
	if (Scenes.find(sceneName) != Scenes.end()) {
		if (currentScene != nullptr) {
			currentScene->Clear();
		}
		currentScene = Scenes[sceneName];

	}
	else
	{
		std::cerr << "ERROR: Scene '" << sceneName << "' not found!\n";
	}
}

void SceneManager::Clear() {
	for (auto& pair : Scenes) {
		delete pair.second;
	}
	Scenes.clear();
}


Scene* SceneManager::GetCurrentScene() {
	return currentScene;
}
