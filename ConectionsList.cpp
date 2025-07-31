#include "ConectionsList.h"


ConectionsList::ConectionsList(std::string content, int NodeID) {
	start = new Conection(content, nullptr, NodeID);
	end = start;
	move = start;
}

ConectionsList::ConectionsList(std::string content, int NodeID, int extraUtilitys) {
	start = new Conection(content, nullptr, NodeID);
	end = start;
	move = start;
}

ConectionsList::~ConectionsList() {
	move = start;
	while (move != nullptr) {
		move = move->GetNext();
		delete start;
		start = move;
	}
}

bool ConectionsList::AddConection(std::string content, int NodeID) {
	if (ExistedID(NodeID)) {
		//std::cout << "ERROR: Conection To " << NodeID << " Already Exists" << std::endl;
	}
	move = end;
	end = new Conection(content, move, NodeID);
	return true;
}

bool ConectionsList::AddConection(std::string content, int NodeID, int extraUtilitys) {
	if (ExistedID(NodeID)) {
		//std::cout << "ERROR: Conection To " << NodeID << " Already Exists" << std::endl;
	}
	move = end;
	end = new Conection(content, move, NodeID, extraUtilitys);
	return true;
}

bool ConectionsList::ExistedID(int NodeID) {
	move = start;
	while (move != nullptr) {
		if (move->GetNodeID() == NodeID) {
			return true;
		}
		move = move->GetNext();
	}
	return false;
}

Conection* ConectionsList::GetStart() {
	return start;
}

int ConectionsList::GetConectionOnListPosition(int position) {
	move = start;
	for (int i = 0; i < position; i++) {
		move = move->GetNext();
		if (move == nullptr) {
			return -1;
		}
	}
	return move->GetNodeID();
}

std::string ConectionsList::GetConectionValueOnNodeID(int NodeID) {
	move = start;
	while (move != nullptr) {
		if (move->GetNodeID() == NodeID) {
			return move->GetValue();
		}
		move = move->GetNext();
	}
	return "OOpsie: ewwow code: 001";
}

int ConectionsList::GetConectionExtraUtilitysOnNodeID(int NodeID) {
	move = start;
	while (move != nullptr) {
		if (move->GetNodeID() == NodeID) {
			return move->GetExtraUtilitys();
		}
		move = move->GetNext();
	}
	return -1;
}

int ConectionsList::GetNodeIDWithExtraUtilitys(int extraUtilitys) {
	move = start;
	while (move != nullptr) {
		if (move->GetExtraUtilitys() == extraUtilitys) {
			return move->GetNodeID();
		}
		move = move->GetNext();
	}
	return -1;
}

void ConectionsList::ReplaceValuesOnNodeID(std::string content, int NodeID, int extraUtilitys) {
	move = start;
	while(move != nullptr) {
		if (move->GetNodeID() == NodeID) {
			move->ReplaceValues(content, extraUtilitys);
		}
		move = move->GetNext();
	}
	return;
}

int ConectionsList::GetGrade() {
	return end->GetID();
}

bool ConectionsList::DeleteConectionToNodeID(int NodeID) {
	if (!ExistedID(NodeID)) {
		return false;
	}
	if (start->GetNodeID() == NodeID) {
		//std::cout << "There's No Support For Deleting Initial Node In The List" << std::endl;
		return false;
	}
	move = start;
	bool found = false;
	while (move != nullptr) {
		if (found) {
			move->SetID(move->GetID() - 1);
		}
		if (move->GetNodeID() == NodeID) {
			if (start == end) {
				delete start;
				start = nullptr;
				end = nullptr;
				move = nullptr;
				found = true;
				break;
			}
			Conection* Erase = move;
			Conection* Past = nullptr;
			Conection* Next = nullptr;
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
			found = true;
		}
		else {
			move = move->GetNext();
		}
	}
	if (found) {
		return true;
	}
	return false;
}