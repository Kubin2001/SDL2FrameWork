#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_mixer.h"
#include <unordered_map>



class SoundManager
{
    private:
        static std::unordered_map<std::string, Mix_Chunk*> Sounds;
    public:
		static void Innit();

		static void LoadSound(const char* filePath, const std::string& name);

		static void LoadSounds(const std::string& directory);

		static void PlaySound(const std::string& name);

		static Mix_Chunk* GetSound(const std::string& name);

		static bool DeleteSound(const std::string& name);

		static void Clear();
};
