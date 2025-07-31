#include "Conection.h"

Conection::Conection(std::string content, Conection* past, int NodeID) { 
	this->NodeID = NodeID;
	this->content = content;
	this->past = past;

	extraUtilitys = -2;

	next = nullptr;
	mySelf = this;

	if (past == nullptr) {
		ID = 0;
	}
	else {
		past->SetNext(mySelf);
		ID = past->GetID() + 1;
	}
}

Conection::Conection(std::string content, Conection* past, int NodeID, int extraUtilitys) {
	this->NodeID = NodeID;
	this->content = content;
	this->past = past;
	this->extraUtilitys = extraUtilitys;

	next = nullptr;
	mySelf = this;

	if (past == nullptr) {
		ID = 0;
	}
	else {
		past->SetNext(mySelf);
		ID = past->GetID() + 1;
	}
}

bool Conection::SetNext(Conection* next) {
	this->next = next;
	return true;
}

bool Conection::SetID(int ID) {
	this->ID = ID;
	return true;
}

bool Conection::SetPast(Conection* past) {
	this->past = past;
	return true;
}

Conection* Conection::GetNext() {
	return next;
}

Conection* Conection::GetPast() {
	return past;
}

int Conection::GetID() {
	return ID;
}

int Conection::GetNodeID() {
	return NodeID;
}

std::string Conection::GetValue() {
	return content;
}

int Conection::GetExtraUtilitys() {
	return extraUtilitys;
}

void Conection::ReplaceValues(std::string content, int extraUtilitys) {
	this->content = content;
	this->extraUtilitys = extraUtilitys;
}