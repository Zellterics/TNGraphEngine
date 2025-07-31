#pragma once
#include "ConectionsList.h"
#include <iostream>

class Node
{
private:
	void *data;
	int ID, content;
	ConectionsList* conectionList;
	Node* past, * next, * mySelf;
public:
	Node(int content, Node* past);
	~Node();
	bool ConectToNodeID(int content, int NodeID);
	bool ConectToNodeID(int content, int NodeID, int extraUtilitys);
	bool DeleteConectionToNodeID(int NodeID);
	bool ExistedNodeID(int NodeID);
	bool SetContent(int content);
	bool SetID(int NodeID);
	bool SetNext(Node* next);
	bool SetPast(Node* past);
	int GetConectionValueTowardsNodeID(int NodeID);
	int GetContent();
	int GetGrade();
	int GetID();
	int GetNodeIDOnListPosition(int position);
	int GetNodeIDWithExtraUtilitys(int extraUtilitys);
	Node* GetNext();
	Node* GetPast();
	ConectionsList* GetConectionList();
	void *GetData();
	void SetData(void *data);
};