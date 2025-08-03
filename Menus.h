#pragma once
#include "Graph.h"
#include <functional>

class Menus
{
private:
	std::unordered_map<char, std::function<void()>> commands;
	Graph* graph;
public:
	Menus(Graph* graph);
	void PrintActual();
	void PrintEverything();
	void PrintWithNodeID(int NodeID);
	std::string GetInput(bool userInput, std::ifstream &file);
	std::string GetInput();
	bool AlternativeMenu(std::string stringContent);
	void StartGameLoop(std::string& savedInputs, const std::string& fileInput);
	std::ofstream getSaveFileStream(const std::string& fileInput);


	template <typename T>
	T CinFail(T content) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//std::cout << "ERROR: cin overflow, changing the value you entered to 23";
			return (T)23;
		}
		return content;
	}
	std::string CinFail(std::string content) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//std::cout << "ERROR: cin overflow, changing the value you entered to 23";
			return "23";
		}
		return content;
	}
};

namespace Out{
	inline std::string CLEAR_SCREEN = "\033[2J";
    inline std::string CURSOR_TOP_LEFT = "\033[H";
	inline std::string MoveCursorDown(const int& amount) {return ("\033[" + std::to_string(amount) + "B");}
}