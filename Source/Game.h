#pragma once
#include <SDL.h>
#include <memory>
#include "Camera.h"
#include "UI.h"


class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event = {};

	std::unique_ptr<UI> ui;

	ClickBoxList list;

public:
	Game();

	void Start();

	void LogicUpdate();

	void FrameUpdate();

	void Input();

	void Exit();

	void Render();

	~Game();

};
