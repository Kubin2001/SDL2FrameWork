#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include <optional>
#include "UI.h"
#include "Colision.h"
#include "Font.h"
#include "GlobalVariables.h"

//BUTTON


SDL_Texture* TemplateUIElement::GetTexture() {
	return texture;
}

void TemplateUIElement::SetTexture(SDL_Texture* temp) {
	texture = temp;
}

SDL_Rect* TemplateUIElement::GetRectangle() {
	return &rectangle;
}

std::string& TemplateUIElement::GetName() {
	return name;
}

void TemplateUIElement::SetName(const std::string value) {
	name = value;
}

void TemplateUIElement::SetText(std::string temptext) {
	text = temptext;
}

std::string& TemplateUIElement::GetText() {
	return text;
}

float TemplateUIElement::GetTextScale() {
	return textScale;
}
void TemplateUIElement::SetTextScale(float temp) {
	textScale = temp;
}
int TemplateUIElement::GetInterLine() {
	return interLine;
}
void TemplateUIElement::SetInterLine(int temp) {
	interLine = temp;
}

bool TemplateUIElement::GetBorder() {
	return border;
}

Font* TemplateUIElement::GetFont() {
	return font;
}

void TemplateUIElement::SetFont(Font* font) {
	this->font = font;
}

void TemplateUIElement::SetBorder(bool temp) {
	border = temp;
}

int TemplateUIElement::GetBorderThickness() {
	return borderThickness;
}

void TemplateUIElement::SetBorderThickness(const int temp) {
	borderThickness = temp;
	border = true;
}

void TemplateUIElement::SetBorder(const int width, const unsigned char R, const unsigned char G, const unsigned char B) {
	border = true;
	borderThickness = width;
	borderRGB[0] = R;
	borderRGB[1] = G;
	borderRGB[2] = B;
}

int TemplateUIElement::GetTextStartX() {
	return textStartX;
}
void TemplateUIElement::SetTextStartX(int temp) {
	textStartX = temp;
}
int TemplateUIElement::GetTextStartY() {
	return textStartY;
}
void TemplateUIElement::SetTextStartY(int temp) {
	textStartY = temp;
}


void TemplateUIElement::SetColor(const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A) {
	buttonColor[0] = R;
	buttonColor[1] = G;
	buttonColor[2] = B;
	buttonColor[3] = A;
}


void TemplateUIElement::SetBorderRGB(const unsigned char R, const unsigned char G, const unsigned char B) {
	borderRGB[0] = R;
	borderRGB[1] = G;
	borderRGB[2] = B;
}

void TemplateUIElement::SetFontColor(const unsigned char R, const unsigned char G, const unsigned char B) {
	if (font != nullptr) {
		if (font->GetTexture() != nullptr) {
			fontRGB[0] = R;
			fontRGB[1] = G;
			fontRGB[2] = B;
		}
	}
}

void TemplateUIElement::Render(SDL_Renderer* renderer) {
	if (!hidden) {
		if (GetTexture() == nullptr) {
			RenderItslelf(renderer);
		}
		else {
			SDL_RenderCopy(renderer, GetTexture(), NULL, GetRectangle());
		}

		if (hovered && hoverable) {
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, hooverFilter[0], hooverFilter[1], hooverFilter[2], hooverFilter[3]);
			SDL_RenderFillRect(renderer, &rectangle);

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
			SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
		}


		if (GetBorder()) {
			RenderBorder(renderer);
		}

		RenderText(renderer);
	}
}

void TemplateUIElement::RenderItslelf(SDL_Renderer* renderer) {
	if (hovered && hoverable) {
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, buttonColor[0], buttonColor[1], buttonColor[2], buttonColor[3]);
		SDL_RenderFillRect(renderer, &rectangle);

		SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
		SDL_SetRenderDrawColor(renderer, hooverFilter[0], hooverFilter[1], hooverFilter[2], hooverFilter[3]);
		SDL_RenderFillRect(renderer, &rectangle);

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	}
	else{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, buttonColor[0], buttonColor[1], buttonColor[2], buttonColor[3]);

		SDL_RenderFillRect(renderer, &rectangle);

		SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	}
}

void TemplateUIElement::RenderBorder(SDL_Renderer* renderer) {
	SDL_Rect leftLine{ rectangle.x, rectangle.y, borderThickness, rectangle.h };
	SDL_Rect upperLine{ rectangle.x, rectangle.y, rectangle.w, borderThickness };
	SDL_Rect rightLine{ (rectangle.x + rectangle.w - borderThickness), rectangle.y, borderThickness, rectangle.h };
	SDL_Rect downLine{ rectangle.x, (rectangle.y + rectangle.h - borderThickness), rectangle.w, borderThickness };

	SDL_SetRenderDrawColor(renderer, borderRGB[0], borderRGB[1], borderRGB[2], 255);

	SDL_RenderFillRect(renderer, &leftLine);
	SDL_RenderFillRect(renderer, &upperLine);
	SDL_RenderFillRect(renderer, &rightLine);
	SDL_RenderFillRect(renderer, &downLine);

	SDL_SetRenderDrawColor(renderer, Global::defaultDrawColor[0], Global::defaultDrawColor[1], Global::defaultDrawColor[2], 255);
}

void TemplateUIElement::RenderText(SDL_Renderer* renderer) {
	if (font != nullptr) {
		SDL_SetTextureColorMod(font->GetTexture(), 255, 255, 255); // Reset anyway no matter the color
		SDL_SetTextureColorMod(font->GetTexture(), fontRGB[0], fontRGB[1], fontRGB[2]);
		switch (textRenderType) {
			case 1:
				font->RenderText(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
				break;
			case 2:
				font->RenderTextCenter(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
				break;
			case 3:
				font->RenderTextFromRight(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
				break;
			default: // Standardowa opcja
				font->RenderText(renderer, text, rectangle, textScale, interLine, textStartX, textStartY);
				break;
		}

	}
}

void TemplateUIElement::SetRenderTextType(const unsigned short textRenderType) {
	this->textRenderType = textRenderType;
}


bool TemplateUIElement::IsHidden() {
	return hidden;
}

void TemplateUIElement::Hide() {
	hidden = true;
}

void TemplateUIElement::Show() {
	hidden = false;
}

bool TemplateUIElement::IsHovered() {
	return hovered;
}

void TemplateUIElement::SetHover(bool temp) {
	hovered = temp;
}

void TemplateUIElement::SetHoverFilter(const bool filter, const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A, const std::string& sound) {
	this->hoverable = filter;
	hooverFilter[0] = R;
	hooverFilter[1] = G;
	hooverFilter[2] = B;
	hooverFilter[3] = A;
	hooverSound = sound;
}

std::string& TemplateUIElement::GetHooverSound() {
	return hooverSound;
}

//BUTTON
//MassageBox
void TextBox::CheckInteraction(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		SDL_Rect temprect{ event.button.x ,event.button.y,1,1 };
		if (SimpleCollision(*GetRectangle(), temprect)) {
			turnedOn = true;
		}
		else if (!SimpleCollision(*GetRectangle(), temprect) && turnedOn) {
			turnedOn = false;
		}
	}
}

void TextBox::ManageTextInput(SDL_Event& event) {
	if (turnedOn) {
		SDL_StartTextInput();

		if (event.type == SDL_TEXTINPUT) {
			GetText() += event.text.text;
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_RETURN) {
				GetText() += '\n';
			}
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && GetText().length() > 0) {
			GetText().pop_back();
		}
	}

}

//MassageBox
//InteractionBox
bool ClickBox::GetStatus() {
	return status;
}

void ClickBox::SetStatus(bool value) {
	status = value;
}

bool ClickBox::ConsumeStatus() {
	if (status) {
		status = false;
		return true;
	}
	return false;
}

void ClickBox::TurnOn() {
	turnedOn = true;
}

void ClickBox::TurnOff() {
	turnedOn = false;
}

bool ClickBox::IsOn() {
	return turnedOn;
}

void ClickBox::SetClickSound(const std::string& temp) {
	this->clickSound = temp;
}

std::string& ClickBox::GetClickSound() {
	return clickSound;
}
//InteractionBox
//Pop Up Box

int PopUpBox::GetLifeTime() {
	return this->lifeTime;
}

void PopUpBox::SetLifeTime(const int lifeTime) {
	this->lifeTime = lifeTime;
}

//Pop Up Box

//ClickBox List
void ClickBoxList::Innit(UI* ui, ClickBox* main, std::vector<std::string> names, int w, int h, int R, int G, int B, std::string *texts, short space) {
	this->ui = ui;
	mainElement = main;
	Elements.reserve(names.size());
	int y = mainElement->GetRectangle()->y + (mainElement->GetRectangle()->h + space);
	for (size_t i = 0; i < names.size(); i++){
		Elements.emplace_back(
			ui->CreateClickBox(names[i], mainElement->GetRectangle()->x, y, 
				w, h, nullptr, ui->GetFont("arial12px"), texts[i])
		);
		Elements[i]->SetColor(R,G,B);
		Elements.back()->Hide();
		y += (h + space);
	}
	ui->AddListRef(this);
	initalized = true;
}

bool ClickBoxList::IsInitialized() {
	return initalized;
}

bool ClickBoxList::IsExpanded() {
	return expanded;
}

ClickBox* ClickBoxList::Get(short index) {
	return Elements[index];
}


ClickBox* ClickBoxList::Main() {
	return mainElement;
}

std::vector<ClickBox*>& ClickBoxList::GetAll() {
	return Elements;
}

void ClickBoxList::Expand() {
	for (const auto& it : Elements) {
		it->Show();
	}
	expanded = true;
}

void ClickBoxList::Hide() {
	for (const auto& it : Elements) {
		it->Hide();
	}
	expanded = false;
}

void ClickBoxList::Clear() {
	for (const auto& it : Elements) {
		ui->DeleteClickBox(it->GetName());
	}
	Elements.clear();
	if (mainElement != nullptr) {
		ui->DeleteClickBox(mainElement->GetName());
	}
	mainElement = nullptr;
	names.clear();
	ui->RemoveListRef(this);
	initalized = false;
	expanded = false;
}

//ClickBox List
UI::UI(SDL_Renderer* renderer) {
	fontManager = new FontManager();
	this->renderer = renderer;
	lastMousePos.x = -10000000;
	lastMousePos.y = -10000000;
}



void UI::Render() {
	for (const auto& it : Buttons) {
		it->Render(renderer);
	}
	for (const auto& it : TextBoxes) {
		it->Render(renderer);
	}
	for (const auto& it : ClickBoxes) {
		it->Render(renderer);
	}
	for (const auto& it : PopUpBoxes) {
		it->Render(renderer);
	}
}


Button* UI::CreateButton(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
	std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

	if (GetButton(name) != nullptr) {
		std::cout << "Warning name collision button with name: " << name << " already exists addition abborted\n";
		return nullptr;
	}

	Buttons.emplace_back(new Button());
	Button* btn = Buttons.back();
	btn->SetName(name);
	btn->GetRectangle()->x = x;
	btn->GetRectangle()->y = y;
	btn->GetRectangle()->w = w;
	btn->GetRectangle()->h = h;

	btn->SetTexture(texture);

	btn->SetText(text);
	btn->SetTextScale(textScale);
	btn->SetFont(font);
	if (font != nullptr) {
		btn->SetInterLine(font->GetStandardInterline());
	}

	btn->SetTextStartX(textStartX);

	btn->SetTextStartY(textStartY);

	if (borderThickness > 0) {
		btn->SetBorderThickness(borderThickness);
		btn->SetBorder(true);
	}

	ButtonsMap.emplace(btn->GetName(), btn);
	return btn;
}

TextBox* UI::CreateTextBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
	std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

	if (GetTextBox(name) != nullptr) {
		std::cout << "Warning name collision massage box with name: " << name << " already exists addition abborted\n";
		return nullptr;
	}

	TextBoxes.emplace_back(new TextBox());
	TextBox* tb = TextBoxes.back();
	tb->SetName(name);
	tb->GetRectangle()->x = x;
	tb->GetRectangle()->y = y;
	tb->GetRectangle()->w = w;
	tb->GetRectangle()->h = h;

	tb->SetTexture(texture);

	tb->SetText("");

	tb->SetTextScale(textScale);
	tb->SetFont(font);
	if (font != nullptr) {
		tb->SetInterLine(font->GetStandardInterline());
	}

	tb->SetTextStartX(textStartX);

	tb->SetTextStartY(textStartY);


	if (borderThickness > 0) {
		tb->SetBorderThickness(borderThickness);
		tb->SetBorder(true);
	}

	TextBoxesMap.emplace(tb->GetName(), tb);
	return tb;
}

ClickBox* UI::CreateClickBox(std::string name, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
	std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {

	if (GetClickBox(name) != nullptr) {
		std::cout << "Warning name collision interaction box with name: " << name << " already exists addition abborted\n";
		return nullptr;
	}

	ClickBoxes.emplace_back(new ClickBox());
	ClickBox* cb = ClickBoxes.back();
	cb->SetName(name);
	cb->GetRectangle()->x = x;
	cb->GetRectangle()->y = y;
	cb->GetRectangle()->w = w;
	cb->GetRectangle()->h = h;

	cb->SetTexture(texture);

	cb->SetText(text);

	cb->SetTextScale(textScale);
	cb->SetFont(font);
	if (font != nullptr) {
		cb->SetInterLine(font->GetStandardInterline());
	}

	cb->SetTextStartX(textStartX);

	cb->SetTextStartY(textStartY);

	if (borderThickness > 0) {
		cb->SetBorderThickness(borderThickness);
		cb->SetBorder(true);
	}

	ClickBoxesMap.emplace(cb->GetName(), cb);
	return cb;
}

PopUpBox* UI::CreatePopUpBox(std::string name, int lifeSpan, int x, int y, int w, int h, SDL_Texture* texture, Font* font,
	std::string text, float textScale, int textStartX, int textStartY, int borderThickness) {
	if (GetPopUpBox(name) != nullptr) {
		std::cout << "Warning name collision interaction box with name: " << name << " already exists addition abborted\n";
		return nullptr;
	}

	PopUpBoxes.emplace_back(new PopUpBox());
	PopUpBox* pb = PopUpBoxes.back();
	pb->SetName(name);
	pb->SetLifeTime(lifeSpan);
	pb->GetRectangle()->x = x;
	pb->GetRectangle()->y = y;
	pb->GetRectangle()->w = w;
	pb->GetRectangle()->h = h;

	pb->SetTexture(texture);

	pb->SetText(text);

	pb->SetTextScale(textScale);
	pb->SetFont(font);
	if (font != nullptr) {
		pb->SetInterLine(font->GetStandardInterline());
	}

	pb->SetTextStartX(textStartX);

	pb->SetTextStartY(textStartY);

	if (borderThickness > 0) {
		pb->SetBorderThickness(borderThickness);
		pb->SetBorder(true);
	}

	PopUpBoxesMap.emplace(pb->GetName(), pb);
	return pb;
}

void UI::AddListRef(ClickBoxList* ref) {
	ListReferences.emplace_back(ref);
}

void UI::RemoveListRef(ClickBoxList* ref) {
	std::erase(ListReferences, ref);
}


void UI::CheckHover() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect rect{ x,y,1,1 };
	for (auto& it : Buttons) {
		if (SimpleCollision(*it->GetRectangle(), rect)) {
			it->SetHover(true);
			// patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
			if (it->GetHooverSound() != "") { 
				SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
				if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
					SoundMan::PlaySound(it->GetHooverSound());
				}
			}
		}
		else{
			it->SetHover(false);
		}
	}
	for (auto& it : TextBoxes) {
		if (SimpleCollision(*it->GetRectangle(), rect)) {
			it->SetHover(true);
			// patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
			if (it->GetHooverSound() != "") {
				SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
				if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
					SoundMan::PlaySound(it->GetHooverSound());
				}
			}
		}
		else{
			it->SetHover(false);
		}
	}
	for (auto& it : ClickBoxes) {
		if (SimpleCollision(*it->GetRectangle(), rect)) {
			it->SetHover(true);
			// patrzenie czy mo�e by� wydany d�wi�k tylko wtedy zadzia�a gdy mysz pierwszy raz jest na przycisku
			if (it->GetHooverSound() != "") {
				SDL_Rect prevMousePos{ lastMousePos.x,lastMousePos.y,1,1 };
				if (!SimpleCollision(prevMousePos, *it->GetRectangle())) {
					SoundMan::PlaySound(it->GetHooverSound());
				}
			}
		}
		else{
			it->SetHover(false);
		}
	}
}

void  UI::CheckTextBoxInteraction(SDL_Event& event) {
	for (auto& it : TextBoxes) {
		it->CheckInteraction(event);
	}
}

void UI::ManageTextBoxTextInput(SDL_Event& event) {
	for (auto& it : TextBoxes) {
		it->ManageTextInput(event);
	}
}

void UI::CheckClickBoxes(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONUP) {
		for (size_t i = 0; i < ClickBoxes.size(); i++) {
			if (ClickBoxes[i]->IsOn()) {
				SDL_Rect temprect{ event.button.x ,event.button.y,1,1 };
				if (SimpleCollision(*ClickBoxes[i]->GetRectangle(), temprect)) {
					ClickBoxes[i]->SetStatus(true);
					if (ClickBoxes[i]->GetClickSound() != "") {
						SoundMan::PlaySound(ClickBoxes[i]->GetClickSound());
					}
				}
			}
		}
	}
}

Button* UI::GetButton(const std::string& name) {
	auto btnFind = ButtonsMap.find(name);
	if (btnFind == ButtonsMap.end()) {
		return nullptr;
	}
	return btnFind->second;
}
TextBox* UI::GetTextBox(const std::string& name) {
	auto msBoxFind = TextBoxesMap.find(name);
	if (msBoxFind == TextBoxesMap.end()) {
		return nullptr;
	}
	return msBoxFind->second;
}
ClickBox* UI::GetClickBox(const std::string& name) {
	auto interBoxFind = ClickBoxesMap.find(name);
	if (interBoxFind == ClickBoxesMap.end()) {
		return nullptr;
	}
	return interBoxFind->second;
}

PopUpBox* UI::GetPopUpBox(const std::string& name) {
	auto interBoxFind = PopUpBoxesMap.find(name);
	if (interBoxFind == PopUpBoxesMap.end()) {
		return nullptr;
	}
	return interBoxFind->second;
}

void UI::SetElementColor(const std::string& name, const unsigned char R, const unsigned char G, const unsigned char B) {
	Button* button = GetButton(name);
	if (button != nullptr) {
		button->SetColor(R, G, B);
		return;
	}

	TextBox* textBox = GetTextBox(name);
	if (textBox != nullptr) {
		textBox->SetColor(R, G, B);
		return;
	}

	ClickBox* clickBox = GetClickBox(name);
	if (clickBox != nullptr) {
		clickBox->SetColor(R, G, B);
		return;
	}
}

void UI::SetElementBorderColor(const std::string& name, const unsigned char R, const unsigned char G, const unsigned char B) {
	Button* button = GetButton(name);
	if (button != nullptr) {
		button->SetBorderRGB(R, G, B);
		return;
	}

	TextBox* textBox = GetTextBox(name);
	if (textBox != nullptr) {
		textBox->SetBorderRGB(R, G, B);
		return;
	}

	ClickBox* clickBox = GetClickBox(name);
	if (clickBox != nullptr) {
		clickBox->SetBorderRGB(R, G, B);
		return;
	}
}

void UI::SetElementFontColor(const std::string& name, const unsigned char R, const unsigned char G, const unsigned char B) {
	Button* button = GetButton(name);
	if (button != nullptr) {
		button->SetFontColor(R, G, B);
		return;
	}

	TextBox* textBox = GetTextBox(name);
	if (textBox != nullptr) {
		textBox->SetFontColor(R, G, B);
		return;
	}

	ClickBox* clickBox = GetClickBox(name);
	if (clickBox != nullptr) {
		clickBox->SetFontColor(R, G, B);
		return;
	}
}

void UI::FrameUpdate() {
	for (auto it = PopUpBoxes.begin(); it != PopUpBoxes.end();) {
		(*it)->lifeTime--;
		if ((*it)->lifeTime < 1) {
			DeletePopUpBox((*it)->name);
			return;
		}
		else {
			++it;
		}
	}
}

void UI::ManageInput(SDL_Event& event) {
	CheckHover();

	CheckTextBoxInteraction(event);

	ManageTextBoxTextInput(event);

	CheckClickBoxes(event);

	SDL_GetMouseState(&lastMousePos.x, &lastMousePos.y);
}

bool UI::DeleteButton(const std::string& name) {
	ButtonsMap.erase(name);
	for (size_t i = 0; i < Buttons.size(); i++){
		if (Buttons[i]->GetName() == name) {
			delete Buttons[i];
			Buttons.erase(Buttons.begin() + i);
			return true;
		}
	}
	return false;
}

bool UI::DeleteTextBox(const std::string& name) {
	TextBoxesMap.erase(name);
	for (size_t i = 0; i < TextBoxes.size(); i++){
		if (TextBoxes[i]->GetName() == name) {
			delete TextBoxes[i];
			TextBoxes.erase(TextBoxes.begin() + i);
			return true;
		}
	}
	return false;
}

bool UI::DeleteClickBox(const std::string& name) {
	ClickBoxesMap.erase(name);
	for (size_t i = 0; i < ClickBoxes.size(); i++){
		if (ClickBoxes[i]->GetName() == name) {
			delete ClickBoxes[i];
			ClickBoxes.erase(ClickBoxes.begin() + i);
			return true;
		}
	}
	return false;
}

bool UI::DeletePopUpBox(const std::string& name) {
	PopUpBoxesMap.erase(name);
	for (size_t i = 0; i < PopUpBoxes.size(); i++) {
		if (PopUpBoxes[i]->GetName() == name) {
			delete PopUpBoxes[i];
			PopUpBoxes.erase(PopUpBoxes.begin() + i);
			return true;
		}
	}
	return false;
}

bool UI::DeleteAnyButton(const std::string& name) {
	if (DeleteButton(name)) { return true; }
	if (DeleteTextBox(name)) { return true; }
	if (DeleteClickBox(name)) { return true; }
	if (DeletePopUpBox(name)) { return true; }
	return false;
}

std::vector<Button*>& UI::GetButtons() {
	return Buttons;
}

std::vector<TextBox*>& UI::GetTextBoxes() {
	return TextBoxes;
}

std::vector<ClickBox*>& UI::GetClickBoxes() {
	return ClickBoxes;
}

std::vector<PopUpBox*>& UI::GetPopUpBoxes() {
	return PopUpBoxes;
}

void UI::CreateFont(const std::string& name, SDL_Texture* texture, const std::string& jsonPath) {
	fontManager->CreateFont(name, texture, jsonPath);
}

Font* UI::GetFont(const std::string& name) {
	return fontManager->GetFont(name);
}

void UI::ScanFont(const std::string& texturePath, const std::string& charactersDataPath,
	unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB, Point size,
	const std::string& outputPath) {
	fontManager->ScanFont(texturePath, charactersDataPath, fR, fG, fB, bR, bG, bB, size.x, size.y);
}

void UI::ClearAll(bool clearLists) {
	if (clearLists) {
		for (auto& it : ListReferences) {
			it->Clear();
		}

		ListReferences.clear();
	}

	for (auto& it : Buttons) {
		delete it;
	}
	for (auto& it : TextBoxes) {
		delete it;
	}
	for (auto& it : ClickBoxes) {
		delete it;
	}
	Buttons.clear();
	TextBoxes.clear();
	ClickBoxes.clear();
	ButtonsMap.clear();
	TextBoxesMap.clear();
	ClickBoxesMap.clear();
}



UI::~UI() {
	ClearAll();
	delete fontManager;
}
