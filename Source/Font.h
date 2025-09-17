#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <array>

#include "Addons.h"


constexpr std::array<char32_t, 200> MakeCharset() {
	std::array<char32_t, 200> cs{};
	for (size_t i = 0; i < cs.size(); i++) {
		cs[i] = (char32_t)(i);
	}
	return cs;
}

static constexpr std::array<char32_t, 200> charset = MakeCharset();

class Font {
private:
	std::string name;
	SDL_Texture* texture = nullptr;
	SDL_Rect rectangle{ 0,0,0,0 };
	std::vector<SDL_Rect> sourceRectangles;
	int standardInterLine = 0;
public:
	Font(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

	std::string GetName();

	SDL_Rect* GetRectangle();

	SDL_Texture* GetTexture();

	int GetStandardInterline();

	void SetStandardInterline(int temp);

	void SetTexture(SDL_Texture* temptex);

	bool LoadTextInfo(const std::string& jsonPath);

	void RenderText(SDL_Renderer* renderer, const std::string& text, SDL_Rect &btnRect, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);

	void RenderTextCenter(SDL_Renderer* renderer, const std::string& text, SDL_Rect &btnRect, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);

	void RenderTextFromRight(SDL_Renderer* renderer, const std::string& text, SDL_Rect& btnRect, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);

	void RenderTextCenterX(SDL_Renderer* renderer, const std::string& text, SDL_Rect& btnRect, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);

	void RenderTextCenterY(SDL_Renderer* renderer, const std::string& text, SDL_Rect& btnRect, float scale = 1.0, int interline = 20, int textStartX = 0, int textStartY = 0);

	Point CalculatePredefinedSize(const std::string& fontText, const int interline, const float scale);
};

class FontManager {
private:

public:
	std::vector<Font*> fonts;

	FontManager();

	bool CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

	Font* GetFont(const std::string& name);

	void ScanFont(const std::string& texturePath, const std::string& charactersDataPath,
		unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB, int width, int height
	, const std::string& outputPath = "font.json");

	~FontManager();
};

void CrateFontFromTTF(const char* ttfPath, const int size, const std::string& name, const std::string& outPath = "");