#include "Files.h"
#include <fstream>
#include <iostream>

std::vector<std::string> ReadCsvLine(const std::string& line, const char separator) {
	std::vector<std::string> items;
	std::string temp = "";
	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] != separator) {
			temp += line[i];
		}
		else {
			items.emplace_back(temp);
			temp.clear();
		}
	}
	items.emplace_back(temp);
	return items;
}

std::vector<std::vector<std::string>> ReadCsv(const std::string& path, const char separator) {
	std::vector<std::vector<std::string>> csvVec;
	std::ifstream csvFile(path);
	std::string line;
	if (csvFile.is_open()) {
		while (std::getline(csvFile, line)) {
			csvVec.emplace_back(ReadCsvLine(line, separator));
		}
		csvFile.close();
	}
	else {
		std::cout << "error reading file\n";
	}

	return csvVec;
}

bool FileExplorer::Open(const std::string& path) {
	window = SDL_CreateWindow("FileWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		200, 300, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

	std::filesystem::path current = std::filesystem::current_path();
	std::cout << "CurrentPath: " << current << '\n';

	texMan.Start(renderer);
	texMan.LoadMultiple("Textures/FileExplorer");
	ui = new UI(renderer);
	Button *btn = ui->CreateButton("Test", 20, 20, 20, 20, texMan.GetTex("FeFolderIcon"), nullptr);
	//btn->SetBorder(2, 180, 180, 180);

	btn = ui->CreateButton("Test2", 20, 50, 20, 20, texMan.GetTex("FeFileIcon"), nullptr);
	//btn->SetBorder(2, 180, 180, 180);

	btn = ui->CreateButton("Test3", 20, 80, 20, 20, texMan.GetTex("FeFolderIcon"), nullptr);
	//btn->SetBorder(2, 180, 180, 180);

	SDL_RenderClear(renderer);
	ui->Render();
	SDL_RenderPresent(renderer);
	return true;
}