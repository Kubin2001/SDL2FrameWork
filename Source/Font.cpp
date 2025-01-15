#include <iostream>
#include <SDL.h>
#include "Font.h"
#include "json.hpp"
#include <fstream>

Font::Font(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
    this->name = name;
    this->texture = texture;
    LoadTextInfo(jsonPath);
}


std::string Font::GetName() {
    return name;
}

SDL_Texture* Font::GetTexture() {
    return texture;
}


void Font::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

SDL_Rect* Font::GetRectangle() {
    return &rectangle;
}

bool Font::LoadTextInfo(const std::string& jsonPath) {
    sourceRectangles.resize(200);
    std::ifstream file(jsonPath);
    if (file.is_open()) {
        nlohmann::json jsonData;
        file >> jsonData;

        for (auto& [key, value] : jsonData.items()) {
            if (std::stoi(key) < sourceRectangles.size()) {
                sourceRectangles[std::stoi(key)].x = value["x"].get<int>();
                sourceRectangles[std::stoi(key)].y = value["y"].get<int>();
                sourceRectangles[std::stoi(key)].w = value["width"].get<int>();
                sourceRectangles[std::stoi(key)].h = value["height"].get<int>();
                if (standardInterLine < sourceRectangles[std::stoi(key)].h) {
                    standardInterLine = sourceRectangles[std::stoi(key)].h;
                }
            }
        }

        /*for (size_t i = 0; i < sourceRectangles.size(); i++)
        {
            std::cout << i << " : X: " << sourceRectangles[i].x << " Y: " << sourceRectangles[i].y
                << " W: " << sourceRectangles[i].w << " H: " << sourceRectangles[i].h << "\n";

        }*/
        //std::cout << "InterLine: " << standardInterLine << "\n";

    }
    else
    {
        std::cout << "Error font json not loaded correctly!\n";
        return false;
    }
    return true;
}

void Font::RenderText(SDL_Renderer* renderer, std::string text, SDL_Rect &btnRect, float scale, int interline, int textStartX, int textStartY) {
    rectangle.x = btnRect.x + textStartX;
    rectangle.y = btnRect.y + textStartY;
    rectangle.w = 0;
    rectangle.h = 0;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < sourceRectangles.size()) {
            if (text[i] != '\n') {
                rectangle.w = sourceRectangles[text[i]].w * scale;
                rectangle.h = sourceRectangles[text[i]].h * scale;
                SDL_RenderCopy(renderer, texture, &sourceRectangles[text[i]], &rectangle);
                rectangle.x += (sourceRectangles[text[i]].w * scale) + 1;
            }
            else
            {
                rectangle.y += interline * scale;
                rectangle.x = temp;
            }
        }
    }
}

void Font::RenderTextCenter(SDL_Renderer* renderer, std::string text, SDL_Rect &btnRect, float scale, int interline, int textStartX, int textStartY) {
    Point textSizes = CalculatePredefinedSize(text,interline);

    textSizes.x *= 0.5;
    textSizes.y *= 0.5;
    Point center = GetRectangleCenter(btnRect);
    rectangle.x = center.x + textStartX - textSizes.x;
    rectangle.y = center.y + textStartY - textSizes.y;
    rectangle.w = 0;
    rectangle.h = 0;
    int temp = rectangle.x;


    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < sourceRectangles.size()) {
            if (text[i] != '\n') {
                rectangle.w = sourceRectangles[text[i]].w * scale;
                rectangle.h = sourceRectangles[text[i]].h * scale;
                SDL_RenderCopy(renderer, texture, &sourceRectangles[text[i]], &rectangle);
                rectangle.x += (sourceRectangles[text[i]].w * scale) + 1;
            }
            else
            {
                rectangle.y += interline * scale;
                rectangle.x = temp;
            }
        }
    }
}


void Font::RenderTextFromRight(SDL_Renderer* renderer, std::string text, SDL_Rect& btnRect, float scale, int interline, int textStartX, int textStartY) {
    if (text.empty()) {
        return;
    }

    rectangle.x = (btnRect.x + btnRect.w) - textStartX - (sourceRectangles[text[0]].w * scale);


    rectangle.y = btnRect.y + textStartY;
    rectangle.w = 0;
    rectangle.h = 0;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < sourceRectangles.size()) {
            if (text[i] != '\n') {
                rectangle.w = sourceRectangles[text[i]].w * scale;
                rectangle.h = sourceRectangles[text[i]].h * scale;
                SDL_RenderCopy(renderer, texture, &sourceRectangles[text[i]], &rectangle);
                rectangle.x -= (sourceRectangles[text[i +1]].w * scale) + 1; // Potencially dangerous since in last iter it will acces string null character
            }
            else
            {
                rectangle.y += interline * scale;
                rectangle.x = temp;
            }
        }
    }
}

//Only use if button text is static and will not change between frames
void Font::RenderTextCenterPred(SDL_Renderer* renderer, std::string text, SDL_Rect& btnRect, Point& textSizes, float scale, int interline, int textStartX, int textStartY) {
    textSizes.x *= 0.5;
    textSizes.y *= 0.5;
    Point center = GetRectangleCenter(btnRect);
    rectangle.x = center.x + textStartX - textSizes.x;
    rectangle.y = center.y + textStartY - textSizes.y;
    rectangle.w = 0;
    rectangle.h = 0;
    int temp = rectangle.x;


    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] < sourceRectangles.size()) {
            if (text[i] != '\n') {
                rectangle.w = sourceRectangles[text[i]].w * scale;
                rectangle.h = sourceRectangles[text[i]].h * scale;
                SDL_RenderCopy(renderer, texture, &sourceRectangles[text[i]], &rectangle);
                rectangle.x += (sourceRectangles[text[i]].w * scale) + 1;
            }
            else
            {
                rectangle.y += interline * scale;
                rectangle.x = temp;
            }
        }
    }
}


Point Font::CalculatePredefinedSize(const std::string& fontText, int interline) {
    Point predSize(0, 0 + interline);
    bool firstLine = true;
    for (int i = 0; i < fontText.length(); i++)
    {
        if (fontText[i] < sourceRectangles.size()) {
            if (fontText[i] != '\n') {
                if (firstLine) {
                    predSize.x += sourceRectangles[fontText[i]].w;
                }

            }
            else
            {
                predSize.y += interline;
                firstLine = false;
            }
        }
    }

    return predSize;
}

int Font::GetStandardInterline() {
    return standardInterLine;
}

void Font::SetStandardInterline(int temp) {
    standardInterLine = temp;
}


/// //////////////////

FontManager::FontManager() {
}


bool FontManager::CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
    if (fonts.size() > 0) {
        for (auto& it : fonts) {
            if (it->GetName() == name) {
                return false;
            }
        }
    }
    fonts.emplace_back(new Font(name, texture, jsonPath));
    return true;
}

Font* FontManager::GetFont(const std::string& name) {
    if (fonts.size() > 0) {
        for (auto& it : fonts) {
            if (it->GetName() == name) {
                return it;
            }
        }
    }
    return nullptr;
}

FontManager::~FontManager() {
    for (auto& it : fonts) {
        delete it;
    }
    fonts.clear();
}