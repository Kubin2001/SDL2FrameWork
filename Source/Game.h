#pragma once
#include <SDL.h>
#include <memory>
#include "Camera.h"
#include "UI.h"


class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    std::unique_ptr<Camera> camera;
    std::unique_ptr<UI> ui;


public:
    Game();

    void Start();

    void LoadTextures();

    void GameLogic();

    void EventsLogic();

    void GameConstant();

    void EventsConstant();

    void Exit();

    void Render();

    ~Game();

};
