#include "Graph.h"

Graph::Graph(std::string content) {
	start = new Node(content, nullptr);
	move = start;
	end = start;
	actual = start;
}
Graph::Graph() {
	start = nullptr;
	move = nullptr;
	end = nullptr;
	actual = nullptr;
}

Graph::~Graph() {
	while (actual != nullptr) {
		DeleteActual();
	}
}

void* Graph::GetActualData() {
	return actual->GetData();
}

void Graph::SetActualData(void* data) {
	return actual->SetData(data);
}

bool Graph::AddNode(std::string content) {
	if (start == nullptr) {
		start = new Node(content, nullptr);
		move = start;
		end = start;
		actual = start;
		return true;
	}
	move = end;
	end = new Node(content, move);
	actual = end;
	return true;
}

ConectionsList* Graph::GetActualConections() {
	if (actual == nullptr) {
		//std::cout << "ERROR: There's No Actual Node" << std::endl;
		ConectionsList* fail = new ConectionsList("OOpsie: ewwow code: 002", -1);
		return fail;
	}
	return actual->GetConectionList();
}

bool Graph::ConectToNodeID(std::string content, int NodeID) {
	if (start == nullptr) {
		//std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return false;
	}
	if (!ExistedID(NodeID)) {
		//std::cout << "ERROR: NODE " << NodeID << " DOESN'T EXISTS" << std::endl;
		return false;
	}
	actual->ConectToNodeID(content, NodeID);
	return true;
}

bool Graph::ChangeActualNodeContent(std::string content) {
	if (start == nullptr) {
		//std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return false;
	}
	actual->SetContent(content);
	return true;
}

bool Graph::ExistedID(int NodeID) {
	move = start;
	while (move != nullptr) {
		if (move->GetID() == NodeID) {
			return true;
		}
		move = move->GetNext();
	}
	return false;
}

bool Graph::GoToNodeID(int NodeID) {
	if (start == nullptr) {
		//std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return false;
	}
	move = start;
	while (move != nullptr) {
		if (move->GetID() == NodeID) {
			actual = move;
			return true;
		}
		move = move->GetNext();
	}
	return false;
}

bool Graph::MoveToNodeID(int NodeID) {
	if (actual == nullptr) {
		//std::cout << "ERROR: There's No Actual Node" << std::endl;
		return false;
	}
	if (actual->ExistedNodeID(NodeID)) {
		GoToNodeID(NodeID);
		return true;
	}
	else {
		return false;
	}
}

int Graph::CountNodes() {
	move = start;
	if (actual == nullptr) {
		return 0;
	}
	int i = 1;
	while (move->GetNext() != nullptr) {
		move = move->GetNext();
		i++;
	}
	return i;
}

Node* Graph::GetActualNode() {
	return actual;
}

Node* Graph::GetEndNode() {
	return end;
}

Node* Graph::GetNextNode() {
	return actual->GetNext();
}

Node* Graph::GetNodeWithID(int NodeID) {
	if (start == nullptr) {
		//std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return nullptr;
	}
	move = start;
	while (move != nullptr) {
		if (move->GetID() == NodeID) {
			return move;
		}
		move = move->GetNext();
	}
	return nullptr;
}

Node* Graph::GetPastNode() {
	return actual->GetPast();
}

Node* Graph::GetStartNode() {
	return start;
}

bool Graph::DualConectToNodeID(std::string content, int NodeID) {
	if (start == nullptr) {
		//std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return false;
	}
	if (NodeID > end->GetID()) {
		//std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
		return false;
	}
	actual->ConectToNodeID(content, NodeID);
	move = GetNodeWithID(NodeID);
	move->ConectToNodeID(content, actual->GetID());
	return true;
}

bool Graph::DeleteActual() {
	if (actual == nullptr) {
		//std::cout << "ERROR: There's No Actual Node" << std::endl;
		return false;
	}
	move = start;
	while (move != nullptr) {
		if (move != actual) {
			move->DeleteConectionToNodeID(actual->GetID());
		}
		move = move->GetNext();
	}
	move = actual;
	if (start == end) {
		delete start;
		start = nullptr;
		end = nullptr;
		move = nullptr;
		actual = nullptr;
		return true;
	}
	Node* Erase = move;
	Node* Past = nullptr;
	Node* Next = nullptr;
	if (move->GetPast() != nullptr) {
		Past = move->GetPast();
		if (move->GetNext() != nullptr) {
			Past->SetNext(move->GetNext());
		}
		else {
			Past->SetNext(nullptr);
			end = Past;
		}
	}
	if (move->GetNext() != nullptr) {
		Next = move->GetNext();
		if (move->GetPast() != nullptr) {
			Next->SetPast(move->GetPast());
		}
		else {
			Next->SetPast(nullptr);
			start = Next;
		}
	}
	move = move->GetNext();
	delete(Erase);
	actual = start;
	return true;
}

bool Graph::DeleteConectionToNodeID(int NodeID) {
	if (actual == nullptr) {
		//std::cout << "ERROR: There's No Actual Node" << std::endl;
		return false;
	}
	if (!actual->ExistedNodeID(NodeID)) {
		//std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
	}
	return actual->DeleteConectionToNodeID(NodeID);
}

bool Graph::DeleteConectionToNodeID(int NodeID, bool DeleteDual) {
	if (actual == nullptr) {
		//std::cout << "ERROR: There's No Actual Node" << std::endl;
		return false;
	}
	if(!actual->ExistedNodeID(NodeID)) {
		//std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
	}
	if (!DeleteDual) {
		return DeleteConectionToNodeID(NodeID);
	}
	move = GetNodeWithID(NodeID);
	actual->DeleteConectionToNodeID(NodeID);
	move->DeleteConectionToNodeID(actual->GetID());
	return false;
}

/*
TEST:
//a 0 a 1 a 2 a 3 a 4 a 5 a 6 a 7 a 8 a 9 a 10 g 0 c 2 1 c 1 2 g 1 c 2 0 c 3 3 g 2 c 1 4 c 1 6 g 3 c 3 1 g 4 c 3 5 c 6 0 g 5 c 4 6 g 6 c 5 4 c 1 3 c 1 7 g 7 c 1 8 g 8 c 1 9 g 9 c 3 10 g 6
*/
