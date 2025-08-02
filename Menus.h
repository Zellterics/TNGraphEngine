#pragma once
#include "Graph.h"

class Menus
{
private:
	struct Data {
		std::string name = "";
		std::string lastName = "";
		int age = 0;
		int reg = 0;
	};
public:
	Menus(Graph* graph);
	
	void PrintActual(Graph* graph);
	void PrintEverything(Graph* graph);
	void PrintWithNodeID(Graph* graph, int NodeID);
	std::string UserInput(bool userInput, std::ifstream &file);


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