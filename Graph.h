#pragma once
#include "Node.h"
#include <iostream>
#include <vector>

class Graph
{
protected:
	Node* start, * move, * end, * actual;
public:
	Graph();
	Graph(std::string content);
	~Graph();
	bool AddNode(std::string content);
	bool ConectToNodeID(std::string content, int NodeID);
	bool ChangeActualNodeContent(std::string content);
	bool DeleteActual();
	bool DeleteConectionToNodeID(int NodeID);
	bool DeleteConectionToNodeID(int NodeID, bool DeleteDual);
	bool DualConectToNodeID(std::string content, int NodeID);
	bool ExistedID(int NodeID);
	bool GoToNodeID(int NodeID);
	bool MoveToNodeID(int NodeID);
	ConectionsList* GetActualConections();
	int CountNodes();
	Node* GetActualNode();
	Node* GetEndNode();
	Node* GetNextNode();
	Node* GetNodeByContent(std::string content);
	Node* GetNodeWithID(int NodeID);
	Node* GetPastNode();
	Node* GetStartNode();

	void* GetActualData();
	void SetActualData(void* data);
};