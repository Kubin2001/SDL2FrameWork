#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>

class Animation {
	public:
		std::vector<SDL_Rect> clips;
		unsigned int firstFrame = 0;
		unsigned int lastFrame = 0;
		unsigned short frameDelay = 20;
};

class Animator {
	private:
		static std::unordered_map<std::string, Animation> Animations;

	public:
		static void CreateNew(const std::string& name, const int clipsAmount, const short frameWidth,
			const short frameHeight, const int frameDelay);

		static SDL_Rect* Get(const std::string& key);

		static void Reset(const std::string& key);

		static bool ClearSingle(const std::string& key);

		static void ClearAll();
};
