#pragma once
#include <iostream>
#include <SDL.h>
#include "GlobalVariables.h"
#include "Addons.h"

class Camera
{
    private:
        SDL_Rect rectangle{0,0,Global::windowWidth,Global::windowHeight};
        float zoom = 1.0f; // Base zoom =1 (or no zoom)
        float zoomRelativeMoveSpeed = 1.0f;

        bool useBorders = false;

    public:
        Camera(bool useBorders);

        float GetZoom();

        SDL_Rect* GetRectangle();

        void UpdatePosition(const SDL_Event& event, const Uint8* state);

        SDL_Rect CalcScreenPosition(const SDL_Rect& rect);

        SDL_Rect CalcScreenPositionWithZoom(const SDL_Rect& rect);

        Point RecoverPosition(int x, int y);

        Point RecoverZoomPosition(int x, int y);

        ~Camera();
};
