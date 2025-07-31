#pragma once
#include <iostream>

class Conection
{
private:
	int ID, NodeID, extraUtilitys;
	std::string content;
	Conection* past, *next, *mySelf;
public:
	Conection(std::string content, Conection* past, int NodeID);
	Conection(std::string content, Conection* past, int NodeID, int extraUtilitys);
	bool SetID(int ID);
	bool SetNext(Conection* next);
	bool SetPast(Conection* past);
	Conection* GetNext();
	Conection* GetPast();
	int GetExtraUtilitys();
	int GetID();
	int GetNodeID();
	std::string GetValue();
	void ReplaceValues(std::string content, int extraUtilitys);
};