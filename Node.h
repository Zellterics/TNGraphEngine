#pragma once
#include "ConectionsList.h"
#include <iostream>

class Node
{
private:
	void *data;
	int ID;
	std::string content;
	ConectionsList* conectionList;
	Node* past, * next, * mySelf;
public:
	Node(std::string content, Node* past);
	~Node();
	bool ConectToNodeID(std::string content, int NodeID);
	bool ConectToNodeID(std::string content, int NodeID, int extraUtilitys);
	bool DeleteConectionToNodeID(int NodeID);
	bool ExistedNodeID(int NodeID);
	bool SetContent(std::string content);
	bool SetID(int NodeID);
	bool SetNext(Node* next);
	bool SetPast(Node* past);
	std::string GetConectionValueTowardsNodeID(int NodeID);
	std::string GetContent();
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