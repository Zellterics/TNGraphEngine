#pragma once
#include "Conection.h"

class ConectionsList
{
private:
	Conection* start, * end, * move;
public:
	ConectionsList(int content, int NodeID);
	ConectionsList(int content, int NodeID, int extraUtilitys);
	~ConectionsList();
	bool AddConection(int content, int NodeID);
	bool AddConection(int content, int NodeID, int extraUtilitys);
	bool DeleteConectionToNodeID(int NodeID);
	bool ExistedID(int NodeID);
	Conection* GetStart();
	int GetConectionExtraUtilitysOnNodeID(int NodeID);
	int GetConectionOnListPosition(int position);
	int GetConectionValueOnNodeID(int NodeID);
	int GetGrade();
	int GetNodeIDWithExtraUtilitys(int extraUtilitys);
	void ReplaceValuesOnNodeID(int content, int NodeID, int extraUtilitys);
};