#include "LinkedList.h"

LinkedList::LinkedList() : Graph() {
	
}

bool LinkedList::AddElement(int content) {
	Node* past = nullptr;
	move = start;
	while (move != nullptr) {
		if (move->GetNodeIDOnListPosition(1) == -1) {
			past = move;
			break;
		}
		move = move->GetNext();
	}
	if (past == nullptr) {
		AddNode(content);
		return true;
	}
	AddNode(content);
	past->ConectToNodeID(1, actual->GetID());
	return true;
}

bool LinkedList::AddNextToActual(int content) {
	if (actual->GetNodeIDOnListPosition(1) == -1) {
		AddElement(content);
	}
	Node* save = actual;
	AddNode(content);
	actual->ConectToNodeID(1, save->GetNodeIDOnListPosition(1));
	save->DeleteConectionToNodeID(save->GetNodeIDOnListPosition(1));
	save->ConectToNodeID(1, actual->GetID());
	return true;
}

bool LinkedList::DeleteActual() {
	Node* past = GetPastOfNode(actual);
	
	if (past == nullptr) {
		Graph::DeleteActual();
		return true;
	}
	if (actual->GetNodeIDOnListPosition(1) == -1) {
		Graph::DeleteActual();
		return true;
	}
	past->ConectToNodeID(1, actual->GetNodeIDOnListPosition(1));
	Graph::DeleteActual();
	return true;
}

Node* LinkedList::GetPastOfNode(Node* found) {
	move = start;
	Node* past = nullptr;
	while (move != nullptr) {
		if (move->ExistedNodeID(found->GetID()) && move != actual) {
			past = move;
			break;
		}
		move = move->GetNext();
	}
	return past;
}