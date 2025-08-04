#include <iostream>
#include <string>
#include <algorithm>
#include "Menus.h"

int main(){
	Graph game;
	Menus menu(&game);
	menu.LegacyMenu();
	menu.LoadGamesMenu();
	menu.StartGameLoop();
	menu.GetInput();
	return 0;
}