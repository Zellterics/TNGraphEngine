#pragma once
#include <iostream>

class Conection
{
private:
	int ID, content, NodeID, extraUtilitys;
	Conection* past, *next, *mySelf;
public:
	Conection(int content, Conection* past, int NodeID);
	Conection(int content, Conection* past, int NodeID, int extraUtilitys);
	bool SetID(int ID);
	bool SetNext(Conection* next);
	bool SetPast(Conection* past);
	Conection* GetNext();
	Conection* GetPast();
	int GetExtraUtilitys();
	int GetID();
	int GetNodeID();
	int GetValue();
	void ReplaceValues(int content, int extraUtilitys);
};