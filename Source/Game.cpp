#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Game.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "SceneManager.h"


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
    TextureManager::Start(renderer);
    SoundManager::Innit();

    camera = std::make_unique<Camera>(0);
    ui = std::make_unique<UI>(renderer);
    LoadTextures();
    ui->CreateFont("arial40px", TextureManager::GetTextureByName("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TextureManager::GetTextureByName("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TextureManager::GetTextureByName("arial12px"), "Textures/Interface/Fonts/arial12px.json");

    //Example code to create a simple buttons
    //ui->CreateInteractionBox("box1", 100, 100, 100, 30, TextureManager::GetTextureByName("buttonGrey"), ui->GetFont("arial12px"), "Example text");
    //ui->GetInteractionBoxByName("box1")->SetFontColor(0, 0, 0);
    //ui->GetInteractionBoxByName("box1")->SetRenderTextType(2);

    //ui->CreateInteractionBox("box2", 200, 200, 100, 30, nullptr);
    //ui->GetInteractionBoxByName("box2")->SetButtonColor(30,30,30);
}

void Game::LoadTextures() {
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

    const Uint8* state = SDL_GetKeyboardState(NULL);

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
    TextureManager::Clear();
    SoundManager::Clear();
    SceneManager::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
