#pragma once
#include <iostream>
#include <SDL.h>
#include "GlobalVariables.h"

class Camera
{
    private:
        SDL_Rect rectangle{0,0,Global::windowWidth,Global::windowHeight};
        //SDL_Rect rectangle{0,0,,Global::windowWidth/2,,Global::windowHeight/2};
        //SDL_Rect rectangle{0,0,(,Global::windowWidth - 100),(,Global::windowHeight- 100)};
        float zoom = 1.0f; // Base zoom =1 (or no zoom)
        float zoomRelativeMoveSpeed = 1.0f;

        bool useBorders = false;

    public:
        Camera(bool useBorders);

        float GetZoom();

        SDL_Rect* GetRectangle();

        void UpdatePosition(const Uint8* state);

        ~Camera();
};
