#pragma once
#include <vector>
#include <string>
#include <SDL.h>
#include <filesystem>
#include "UI.h"

std::vector<std::string> ReadCsvLine(const std::string& line, const char separator = ',');

std::vector<std::vector<std::string>> ReadCsv(const std::string& path, const char separator = ',');


class FileExplorer {
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Event event;

		std::string startPath = "";
		std::string currentPath = "";
		std::string retPath = "";
		bool finished = false;

		UI* ui = nullptr;

		LocalTexMan texMan;

		std::vector<ClickBox*> folderElements;

		ClickBox* selectedElement = nullptr;

		std::string Maintain();

		void Input();

		void Update();

	public:
		FileExplorer() = default;

		std::string Open(const std::string& path);



};