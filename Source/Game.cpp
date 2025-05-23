#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Game.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Animator.h"




Game::Game() {
    window = nullptr;
    renderer = nullptr;
    ui = nullptr;
}

void Game::Start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Global::windowWidth, Global::windowHeight, SDL_WINDOW_SHOWN);
    //renderer = SDL_CreateRenderer(window, -1, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Global::defaultDrawColor[0] = 255;
    Global::defaultDrawColor[1] = 255;
    Global::defaultDrawColor[2] = 255;
    SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255); 
    TexMan::Start(renderer);
    TexMan::LoadMultiple("Textures/Examples");
    SoundMan::Innit();
    SoundMan::LoadSounds("Sounds");

    ui = std::make_unique<UI>(renderer);

    ui->CreateFont("arial40px", TexMan::GetTex("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TexMan::GetTex("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TexMan::GetTex("arial12px"), "Textures/Interface/Fonts/arial12px.json");
}


void Game::LogicUpdate() {
    Global::frameCounter++;
}


void Game::FrameUpdate() {
    Input();
    Render();
}




void Game::Input() {
    while (SDL_PollEvent(&event)) {
        ui->ManageInput(event);
        Exit();
    }

    Global::inputDelay++;
}



void Game::Render() {
    SDL_RenderClear(renderer);
    ui->Render();
    SDL_RenderPresent(renderer);
}


void Game::Exit() {
    if (event.type == SDL_QUIT) {
        Global::status = false; 
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        Global::status = false;
    }
}


Game::~Game() {
    TexMan::Clear();
    SoundMan::Clear();
    SceneMan::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
