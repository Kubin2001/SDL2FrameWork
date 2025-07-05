#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "SDL_image.h"
#include "Addons.h"



class TexMan {
	private:
		static std::unordered_map<std::string, SDL_Texture*> Textures;
		static std::vector<std::string> SupportedFormats;
		static SDL_Renderer* renderer;
		static bool isInnit;

	public:

		static bool Start(SDL_Renderer* ren);

		static bool IsWorking();

		static void Print();

		// You need to pass extenstion with . example .png it supports all formats supported by sdl_image IMG_LOAD
		static bool IsFormatSupported(const std::string& format);

		static void LoadSingle(const char* filePath, const std::string& name);

		//Loads single folder and uses file names (without extensions) as keys
		// Example tree.png key = tree
		static void LoadMultiple(const std::string& directory);

		// Recursive loading of every folder and subfolder in directory uses file names (without extensions) as keys
		// Example tree.png key = tree
		static void DeepLoad(const std::string& directory);

		static SDL_Texture* GetTex(const std::string& name);

		static bool DeleteTexture(const std::string& name);

		static Point GetTextureSize(const std::string& name);

		// Function to split texture into multiple smaller textures at runtime
		// Original texture needs to have seperator color at higest pixel at the row and cant use it anywere else
		static void SplitTexture(const char* path, const std::vector<std::string>& names,
			const unsigned char r = 0, const unsigned char g = 0, const unsigned char b = 0, const unsigned char a = 255);

		static void Clear();
};

class LocalTexMan {
	private:
		std::unordered_map<std::string, SDL_Texture*> Textures;
		std::vector<std::string> SupportedFormats;
		SDL_Renderer* renderer;
		bool isInnit;

	public:
		bool Start(SDL_Renderer* ren);

		bool IsWorking();

		void Print();

		// You need to pass extenstion with . example .png it supports all formats supported by sdl_image IMG_LOAD
		bool IsFormatSupported(const std::string& format);

		void LoadSingle(const char* filePath, const std::string& name);

		//Loads single folder and uses file names (without extensions) as keys
		// Example tree.png key = tree
		void LoadMultiple(const std::string& directory);

		// Recursive loading of every folder and subfolder in directory uses file names (without extensions) as keys
		// Example tree.png key = tree
		void DeepLoad(const std::string& directory);

		SDL_Texture* GetTex(const std::string& name);

		bool DeleteTexture(const std::string& name);

		Point GetTextureSize(const std::string& name);

		// Function to split texture into multiple smaller textures at runtime
		// Original texture needs to have seperator color at higest pixel at the row and cant use it anywere else
		void SplitTexture(const char* path, const std::vector<std::string>& names,
			const unsigned char r = 0, const unsigned char g = 0, const unsigned char b = 0, const unsigned char a = 255);

		void Clear();
};
