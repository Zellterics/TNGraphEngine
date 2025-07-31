#pragma once
#include "Graph.h"

class LinkedList:protected Graph
{
public:
	LinkedList();
	bool AddElement(int content);
	bool AddNextToActual(int content);
	bool DeleteActual();
	Node* GetPastOfNode(Node* found);
	using Graph::GoToNodeID;
	using Graph::ChangeActualNodeContent;
	friend class Menus;
};