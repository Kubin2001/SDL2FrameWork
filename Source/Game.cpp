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
    TexMan::Start(renderer);
    SoundMan::Innit();
    SoundMan::LoadSounds("Sounds");

    ui = std::make_unique<UI>(renderer);
    LoadTextures();
    ui->CreateFont("arial40px", TexMan::GetTex("arial40px"), "Textures/Interface/Fonts/arial40px.json");
    ui->CreateFont("arial20px", TexMan::GetTex("arial20px"), "Textures/Interface/Fonts/arial20px.json");
    ui->CreateFont("arial12px", TexMan::GetTex("arial12px"), "Textures/Interface/Fonts/arial12px.json");

    //Example code to create a simple buttons
    //ui->CreateInteractionBox("box1", 100, 100, 100, 30, TextureManager::GetTextureByName("buttonGrey"), ui->GetFont("arial12px"), "Example text");
    //ui->GetInteractionBoxByName("box1")->SetFontColor(0, 0, 0);
    //ui->GetInteractionBoxByName("box1")->SetRenderTextType(2);
    //ui->GetInteractionBoxByName("box1")->SetHoverFilter(1, 255, 255, 255, 120);

    //ui->CreateInteractionBox("box2", 200, 200, 100, 30, nullptr);
    //ui->GetInteractionBoxByName("box2")->SetButtonColor(30,30,30);
    TexMan::LoadMultiple("Textures/Examples");

    /*ui->CreateButton("Button1", 5, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ui->CreateInteractionBox("Button1", 110, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ui->CreateMassageBox("Button1", 215, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);*/

    //Iter1
    /*Button * btnRef = ui->CreateButton("Button1", 5, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    InteractionBox* InteractionBoxRef = ui->CreateInteractionBox("Button1", 110, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    MassageBox* MassageBoxRef = ui->CreateMassageBox("Button1", 215, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);

    MassageBoxRef->GetRectangle()->y = 500;*/

    //Iter 2
    /*Button* btnRef = ui->CreateButton("Button1", 5, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ClickBox* clickBoxRef = ui->CreateClickBox("Button1", 110, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    MassageBox* MassageBoxRef = ui->CreateMassageBox("Button1", 215, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);

    MassageBoxRef->GetRectangle()->y = 500;*/

    //Iter 3
    /*Button* btnRef = ui->CreateButton("Button1", 5, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ClickBox* clickBoxRef = ui->CreateClickBox("Button1", 110, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    TextBox* TextBoxRef = ui->CreateTextBox("Button1", 215, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);

    TextBoxRef->GetRectangle()->y = 500;*/

    //Iter 4
    /*Button* btnRef = ui->CreateButton("Button1", 5, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ClickBox* clickBoxRef = ui->CreateClickBox("Button1", 110, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    TextBox* TextBoxRef = ui->CreateTextBox("Button1", 215, 30, 100, 100, TextureManager::GetTextureByName("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);*/

    //Iter 5
    Button* btnRef = ui->CreateButton("Button1", 5, 30, 100, 100, TexMan::GetTex("granite"), 
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    ClickBox* clickBoxRef = ui->CreateClickBox("Button1", 110, 30, 100, 100, TexMan::GetTex("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);
    TextBox* textBoxRef = ui->CreateTextBox("Button1", 215, 30, 100, 100, TexMan::GetTex("granite"),
        ui->GetFont("arial12px"), "Some example\ntext", 1.0f, 5, 5, 2);

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
