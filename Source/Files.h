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

		std::string startPath = "";

		UI* ui = nullptr;

		LocalTexMan texMan;

	public:
		FileExplorer() = default;

		bool Open(const std::string& path);



};