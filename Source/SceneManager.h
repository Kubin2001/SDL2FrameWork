#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <any>
#include "UI.h"

class Scene {
	protected: 
		std::string name;
		UI* ui = nullptr;
		SDL_Renderer *renderer = nullptr;

	public:
		virtual void Init(SDL_Renderer* renderer = nullptr,UI* ui = nullptr) = 0;

		virtual void GameTimeEvents() = 0; 

		virtual void ConstTimeEvents() = 0;

		virtual void Input(SDL_Event &event) = 0;

		virtual void Render() = 0;

		virtual void Clear() = 0;
};

class SceneManager {
	private:
		static Scene* currentScene;

		static std::unordered_map<std::string, Scene*> Scenes;

		static std::unordered_map<std::string, std::any> SharedData;

	public:
		static void AddScene(Scene *scene, const std::string &sceneName);

		static void SetScene(const std::string& sceneName);

		static void Clear();

		static Scene* GetCurrentScene();
};
