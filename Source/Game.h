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

    void LogicUpdate();

    void FrameUpdate();

    void Input();

    void Exit();

    void Render();

    ~Game();

};
