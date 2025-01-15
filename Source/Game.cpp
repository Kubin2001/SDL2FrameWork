#include <SDL.h>
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "Game.h"
#include "GlobalVariables.h"
#include "TextureManager.h"
#include "SoundManager.h"


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

    // Example code to create a simple button
    //ui->CreateInteractionBox("box1", 100, 100, 100, 30, TextureManager::GetTextureByName("buttonGrey"), ui->GetFont("arial20px"), "some text");
    //ui->GetInteractionBoxByName("box1")->SetFontColor(0, 0, 0);
    //ui->GetInteractionBoxByName("box1")->SetRenderTextType(4);
}

void Game::LoadTextures() {
    ui->LoadTextures();
}

void Game::GameLogic() {
    EventsLogic();
    MovementLogic();
}

void Game::EventsLogic() {
    Global::frameCounter++;
    FiveTickEvents();
}

void Game::MovementLogic() {

}

void Game::FiveTickEvents() {
    if (Global::frameCounter % 5 == 0) {
        //FiveTicks
        //FiveTicks
        if (Global::frameCounter % 20 == 0) {
            TwentyTickEvents();
        }
        if (Global::frameCounter % 50 == 0) {
            FiftyTickEvents();
            if (Global::frameCounter % 100 == 0) {
                HundretTickEvents();
            }
            if (Global::frameCounter % 500 == 0) {
                FiveHundretTickEvents();
            }
        }
    }
}

void Game::TwentyTickEvents() {

}

void Game::FiftyTickEvents() {

}

void Game::HundretTickEvents() {

}

void Game::FiveHundretTickEvents() {

}

void Game::GameConstant() {
    EventsConstant();
    MovementConstant();
    Render();
}




void Game::EventsConstant() {
    while (SDL_PollEvent(&event)) {
        ui->ManageInput(event);
    }
    Global::inputDelay++;
}

void Game::MovementConstant() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    camera->UpdatePosition(state);
    if (Global::inputDelay > 10) {
        if (state[SDL_SCANCODE_C]) {
            Global::inputDelay = 0;
        }
        if (state[SDL_SCANCODE_X]) {
        }
    }
    Exit(state);
}




void Game::Exit(const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        Global::status = false;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    ui->Render();
    SDL_RenderPresent(renderer);
}

Game::~Game() {
    TextureManager::Clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //std::cout << "Resources Destroyed";
}
