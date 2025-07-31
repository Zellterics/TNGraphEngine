#include "Node.h"

Node::Node(int content, Node* past) {
	this->content = content;
	this->past = past;

	next = nullptr;
	mySelf = this;

	if (past == nullptr) {
		ID = 0;
		this->content = content;
	}
	else {
		ID = past->ID + 1;
		past->SetNext(mySelf);
	}
	data = nullptr;
	conectionList = new ConectionsList(0, ID);
}

Node::~Node() {
	delete conectionList;
}

void *Node::GetData() {
	return data;
}

void Node::SetData(void *data) {
	this->data = data;
}

bool Node::ConectToNodeID(int content, int NodeID) {
	if (ExistedNodeID(NodeID)) {
		//std::cout << "ERROR: CONECTION ALREADY EXISTS" << std::endl;
		return false;
	}
	conectionList->AddConection(content, NodeID);
	return true;
}

bool Node::ExistedNodeID(int NodeID) {
	return conectionList->ExistedID(NodeID);
}

int Node::GetContent() {
	return content;
}

int Node::GetConectionValueTowardsNodeID(int NodeID) {
	if (conectionList->GetConectionValueOnNodeID(NodeID) == -1) {
		//std::cout << "ERROR: NodeID Not Found" << std::endl;
	}
	return conectionList->GetConectionValueOnNodeID(NodeID);
}

int Node::GetGrade() {
	return conectionList->GetGrade();
}

int Node::GetID() {
	return ID;
}

int Node::GetNodeIDOnListPosition(int position) {
	return conectionList->GetConectionOnListPosition(position);
}

int Node::GetNodeIDWithExtraUtilitys(int extraUtilitys) {
	return conectionList->GetNodeIDWithExtraUtilitys(extraUtilitys);
}

Node* Node::GetNext() {
	return next;
}

Node* Node::GetPast() {
	return past;
}

ConectionsList* Node::GetConectionList() {
	return conectionList;
}

bool Node::SetContent(int content) {
	this->content = content;
	return true;
}

bool Node::SetID(int NodeID) {
	ID = NodeID;
	return true;
}

bool Node::SetNext(Node* next) {
	this->next = next;
	return true;
}

bool Node::SetPast(Node* past) {
	this->past = past;
	return true;
}

bool Node::DeleteConectionToNodeID(int NodeID) {
	return conectionList->DeleteConectionToNodeID(NodeID);
}

bool Node::ConectToNodeID(int content, int NodeID, int extraUtilitys) {
	if (ExistedNodeID(NodeID)) {
		//std::cout << "ERROR: CONECTION ALREADY EXISTS" << std::endl;
		return false;
	}
	conectionList->AddConection(content, NodeID, extraUtilitys);
	return true;
}