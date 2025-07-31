#pragma once
#include "Conection.h"

class ConectionsList
{
private:
	Conection* start, * end, * move;
public:
	ConectionsList(std::string content, int NodeID);
	ConectionsList(std::string content, int NodeID, int extraUtilitys);
	~ConectionsList();
	bool AddConection(std::string content, int NodeID);
	bool AddConection(std::string content, int NodeID, int extraUtilitys);
	bool DeleteConectionToNodeID(int NodeID);
	bool ExistedID(int NodeID);
	Conection* GetStart();
	int GetConectionExtraUtilitysOnNodeID(int NodeID);
	int GetConectionOnListPosition(int position);
	std::string GetConectionValueOnNodeID(int NodeID);
	int GetGrade();
	int GetNodeIDWithExtraUtilitys(int extraUtilitys);
	void ReplaceValuesOnNodeID(std::string content, int NodeID, int extraUtilitys);
};