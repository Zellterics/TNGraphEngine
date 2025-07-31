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
	Graph(int content);
	~Graph();
	bool AddNode(int content);
	bool ConectToNodeID(int content, int NodeID);
	bool ChangeActualNodeContent(int content);
	bool DeleteActual();
	bool DeleteConectionToNodeID(int NodeID);
	bool DeleteConectionToNodeID(int NodeID, bool DeleteDual);
	bool DualConectToNodeID(int content, int NodeID);
	bool ExistedID(int NodeID);
	bool GoToNodeID(int NodeID);
	bool MoveToNodeID(int NodeID);
	ConectionsList* GetActualConections();
	ConectionsList PathFindingToNodeID(int NodeID);
	int CountNodes();
	Node* GetActualNode();
	Node* GetEndNode();
	Node* GetNextNode();
	Node* GetNodeWithID(int NodeID);
	Node* GetPastNode();
	Node* GetStartNode();
	std::vector<int> DepthFirstSearch(int Data);

	void* GetActualData();
	void SetActualData(void* data);
};