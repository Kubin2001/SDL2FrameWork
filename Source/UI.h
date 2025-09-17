#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <optional>
#include <map>
#include <unordered_map>

#include "Basics.h"
#include "Font.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Button : public GameObject {
	protected:
	SDL_Texture* texture = nullptr;
	SDL_Rect rectangle = { 0,0,0,0 };
	std::string name = "";
	std::string text = "";
	float textScale = 1.0f;
	int interLine = 20;

	bool border = false;

	int borderThickness = 0;

	int textStartX = 0;
	int textStartY = 0;

	unsigned char buttonColor[4] = { 255,255,255,255 };

	unsigned char borderRGB[3] = { 255,255,255 };

	unsigned char fontRGB[3] = { 255,255,255 };

	Font* font = nullptr;

	unsigned short textRenderType = 1;

	Point predefinedSize;

	bool hidden = false;

	bool hovered = false; // Is button in collidion with mouse

	bool hoverable = false; // Is hover filter aplied with mouse collisojn

	unsigned char hooverFilter[4] = { 0,0,0,0 };

	std::string hooverSound = "";

	bool GetBorder();

	void SetBorder(bool temp);

	public:

	SDL_Texture* GetTexture();

	void SetTexture(SDL_Texture* temp);

	SDL_Rect* GetRectangle();

	std::string& GetName();

	void SetName(const std::string value);

	std::string& GetText();
	void SetText(std::string temptext);

	float GetTextScale();
	void SetTextScale(float temp);
	int GetInterLine();
	void SetInterLine(int temp);

	int GetBorderThickness();

	void SetBorderThickness(const int temp);

	void SetBorder(const int width, const unsigned char R, const unsigned char G, const unsigned char B);

	int GetTextStartX();
	void SetTextStartX(int temp);
	int GetTextStartY();
	void SetTextStartY(int temp);

	Font* GetFont();

	void SetFont(Font* font);

	void SetColor(const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A = 255);

	void SetBorderRGB(const unsigned char R, const unsigned char G, const unsigned char B);

	void SetFontColor(const unsigned char R, const unsigned char G, const unsigned char B);

	void Render(SDL_Renderer* renderer);

	void RenderItslelf(SDL_Renderer* renderer);

	void RenderBorder(SDL_Renderer* renderer);

	void RenderText(SDL_Renderer* renderer);

	// 1 Standard
	// 2 Center
	// 3 From Right
	void SetRenderTextType(const unsigned short textRenderType);

	bool IsHidden();

	void Hide();

	void Show();

	bool IsHovered();

	void SetHover(bool temp);

	void SetHoverFilter(const bool filter, const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A, const std::string& sound = "");

	std::string& GetHooverSound();

	friend class UI;
};

// A button that can be clicked with a mouse
class ClickBox : public Button {
	private:
		bool status = false;
		bool turnedOn = true;

		std::string clickSound = "";
	public:
		bool GetStatus();

		void SetStatus(bool value);

		bool ConsumeStatus();

		void TurnOn();

		void TurnOff();

		bool IsOn();

		void SetClickSound(const std::string &temp);

		std::string &GetClickSound();

		friend class UI;
};

// Button that can accept text input
class TextBox : public Button {
	private:
		bool turnedOn = false;
	public:
		void CheckInteraction(SDL_Event& event);

		void ManageTextInput(SDL_Event& event);
		friend class UI;
};

// Basic non interactive button

class PopUpBox : public Button {
	private:
		int lifeTime = 0;

	public:
		friend class UI;

		int GetLifeTime();
		void SetLifeTime(const int lifeTime);
};

class ClickBoxList {
	private:
	UI* ui = nullptr;

	ClickBox* mainElement = nullptr;

	std::vector<ClickBox*> Elements = {};

	bool initalized = false;

	bool expanded = false;

	public:

	void Innit(UI* ui, ClickBox* main, int w, int h, int R, int G, int B, const std::vector<std::string>& texts, short space = 0);

	bool IsInitialized();

	bool IsExpanded();

	ClickBox* Main();

	std::vector<ClickBox*>& GetAll();

	void Expand();

	void Hide();

	void Clear();

	ClickBox* operator [](const size_t index) {
		if (index > Elements.size() - 1) {
			throw std::runtime_error("Click box list element out of index");
		}
		return Elements[index];
	}
};

// To propelly start the UI you need to pleace manage input function in event loop and render in rendering loop
class UI{
private:
	SDL_Renderer* renderer;
	LocalTexMan* localTexMan = nullptr;

	std::vector<Button*> Buttons;
	std::vector<TextBox*> TextBoxes;
	std::vector<ClickBox*> ClickBoxes;
	std::vector<PopUpBox*> PopUpBoxes;

	std::unordered_map<std::string, Button*> ButtonsMap;
	std::unordered_map<std::string, TextBox*> TextBoxesMap;
	std::unordered_map<std::string, ClickBox*> ClickBoxesMap;
	std::unordered_map<std::string, PopUpBox*> PopUpBoxesMap;

	std::vector<ClickBoxList*> ListReferences;

	FontManager* fontManager;

	Point lastMousePos;

public:

	UI(SDL_Renderer* renderer);

	Button* CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture = nullptr, Font* font = nullptr,
		std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

	TextBox* CreateTextBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture = nullptr, Font* font = nullptr,
		std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

	ClickBox* CreateClickBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture = nullptr, Font* font = nullptr,
		std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

	PopUpBox* CreatePopUpBox(std::string name, int lifeSpan, int x, int y, int w, int h, SDL_Texture* texture = nullptr, Font* font = nullptr,
		std::string text = "", float textScale = 1.0f, int textStartX = 0, int textStartY = 0, int borderThickness = 0);

	void AddListRef(ClickBoxList *ref);

	void RemoveListRef(ClickBoxList* ref);

	void CheckHover();

	void CheckTextBoxInteraction(SDL_Event& event);

	void ManageTextBoxTextInput(SDL_Event& event);

	void CheckClickBoxes(SDL_Event& event);

	Button* GetButton(const std::string& name);
	TextBox* GetTextBox(const std::string& name);
	ClickBox* GetClickBox(const std::string& name);
	PopUpBox* GetPopUpBox(const std::string& name);

	void SetElementColor(const std::string& name, const unsigned char R, unsigned char G, unsigned char B);

	void SetElementBorderColor(const std::string& name, const unsigned char R, const unsigned char G, const unsigned char B);
	void SetElementFontColor(const std::string& name, const unsigned char R, const unsigned char G, const unsigned char B);

	void FrameUpdate();

	void ManageInput(SDL_Event& event);

	bool DeleteButton(const std::string& name);

	bool DeleteTextBox(const std::string& name);

	bool DeleteClickBox(const std::string& name);

	bool DeletePopUpBox(const std::string& name);

	bool DeleteAnyButton(const std::string& name);

	void Render();

	std::vector<Button*>& GetButtons();

	std::vector<TextBox*>& GetTextBoxes();

	std::vector<ClickBox*>& GetClickBoxes();

	std::vector<PopUpBox*>& GetPopUpBoxes();

	// You need to provide not name (made up by you) texture (needs to be already loaded by texture manager) path to pregenerated json file
	void CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath);

	Font* GetFont(const std::string& name);

	//Function to create json file for font png file that contains charcter glyps separated by lines in other color than the font
	//Requires provided txt file with ordered glyps
	//Example:
	//A
	//B
	//C
	//And so on...
	void ScanFont(const std::string& texturePath, const std::string& charactersDataPath,
		unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB, Point size,
		const std::string& outputPath);

	void ClearAll(bool clearLists = true);


	~UI();
};
