#include "Menus.h"
#include <fstream>

Menus::Menus(Graph* graph) {
	std::ifstream file;
	int content, NodeID;
	std::string stringContent;
	bool stop = false;
	std::string input;
	char filteredInput;
	bool userInput = true;
	input = 'f';
	while (!stop) {
		filteredInput = input[0];
		switch (filteredInput) {
		case 'f': case 'F':
			std::cout << "---FUNCTIONS    ---\n";
			std::cout << "---AddNode      ---\n";
			std::cout << "---ConectWith   ---\n";
			std::cout << "---GoTo         ---\n";
			std::cout << "---SlideTo      ---\n";
			std::cout << "---WholeSearch  ---\n";
			std::cout << "---Print        ---\n";
			std::cout << "---Everything   ---\n";
			std::cout << "---BorderNodes  ---\n";
			std::cout << "---DeleteActual ---\n";
			std::cout << "---ModifyContent---\n";
			std::cout << "---HowManyNodes ---\n";
			std::cout << "---LoadFromFile ---\n";
			std::cout << "---Terminate    ---\n";
			break;
		case 'a': case 'A':
			if(userInput){
				std::cout << "--->Node content:";
				std::getline(std::cin, stringContent);
			} else {
				if(!std::getline(file, stringContent)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
			}
			stringContent = CinFail(stringContent);
			graph->AddNode(stringContent);
			if (userInput)
				PrintActual(graph);
			break;
		case 'c': case 'C':
			if(userInput){
				std::cout << "--->Conection content:";
				std::getline(std::cin, stringContent);
			} else {
				if(!std::getline(file, stringContent)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
			}
			stringContent = CinFail(stringContent);
			if(userInput){
				std::cout << "--->Conection NodeID:";
				std::cin >> NodeID;
				NodeID = CinFail(NodeID);
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
				NodeID = CinFail(std::stoi(save));
			}
			if(!graph->ConectToNodeID(stringContent, NodeID)){
				std::cout << "already connected" << std::endl;
			}
			if (userInput){
				PrintActual(graph);
				std::cout << "--(" << stringContent << ")-->";
				PrintWithNodeID(graph, NodeID);
			}
			break;
		case 'g': case 'G':
			if(userInput){
				std::cout << "--->NodeID:";
				std::cin >> NodeID;
				NodeID = CinFail(NodeID);
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
				NodeID = CinFail(std::stoi(save));
			}
			if (!graph->GoToNodeID(NodeID)) {
				std::cout << "--->ERROR: No Such NodeID\n";
			}
			if (userInput)
				PrintActual(graph);
			break;
		case 's': case 'S':
			if(userInput){
				std::cout << "--->NodeID:";
				std::cin >> NodeID;
				NodeID = CinFail(NodeID);
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
				NodeID = CinFail(std::stoi(save));
			}
			if (!graph->MoveToNodeID(NodeID)) {
				std::cout << "--->ERROR: Not Such NodeID Conection\n";
			}
			if (userInput)
				PrintActual(graph);
			break;
		case 'p': case 'P':
			PrintActual(graph);
			break;
		case 'e': case 'E':
			PrintEverything(graph);
			break;
		case 'w': case 'W':
			PathFindingToAll(graph);
			break;
		case 't': case 'T':
			stop = true;
			break;
		case 'b': case 'B': {
			ConectionsList* erase = graph->GetActualConections();
			if (erase->GetConectionOnListPosition(0) == -1) {
				delete erase;
			}
			else {
				Conection* move = erase->GetStart();
				while (move != nullptr) {
					std::cout << "\n";
					std::cout << "--(" << move->GetValue() << ", ID:" << move->GetID() << ")-->NodeID[" << move->GetNodeID() << "]";
					move = move->GetNext();
				}
			}}
			break;
		case 'd': case 'D':
			graph->DeleteActual();
			break;
		case 'm': case 'M':
			if(userInput){
				std::cout << "--->Node content:";
				std::getline(std::cin, stringContent);
			} else {
				if(!std::getline(file, stringContent)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
			}
			stringContent = CinFail(stringContent);
			graph->ChangeActualNodeContent(stringContent);
			if (userInput)
				PrintActual(graph);
			break;
		case 'h': case 'H':
			std::cout << "There are " << graph->CountNodes() << " Nodes\n";
			break;
		case 'l' : case 'L':
			std::cout << "File Path: ";
			std::getline(std::cin, stringContent);
			std::cout << stringContent;
			file = std::ifstream(stringContent);
			
			if (!file.is_open()) {
				std::cout << "OOpsie: ewwow code: 004";
				break;
			}
			userInput = false;
			break;
		case 'z':
			if(!userInput){
				userInput = true;
			}
			break;
		default:
			std::cout << "That's Not An Option" << std::endl;
			break;
		}
		if(userInput){
			std::cout << "\n--->";
			std::getline(std::cin, input);
			input = CinFail(input);
		} else {
			if(!std::getline(file, input)){
				std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
			}
		}
	}
}

//Functions


void Menus::PathFindingToAll(Graph* graph) {
	if (graph->GetActualNode() == nullptr) {
		std::cout << "ERROR: There's No Actual Node" << std::endl;
		return;
	}
	ConectionsList NodeSteps("return", graph->GetActualNode()->GetID(), 6);
	Node* move = graph->GetActualNode();
	for (int i = 1;; i++) {
		for (int j = 0; move->GetNodeIDOnListPosition(j) != -1; j++) {
			if (NodeSteps.GetConectionValueOnNodeID(move->GetNodeIDOnListPosition(j)) > (move->GetConectionValueTowardsNodeID(move->GetNodeIDOnListPosition(j)) + NodeSteps.GetConectionValueOnNodeID(move->GetID()))) {
				NodeSteps.ReplaceValuesOnNodeID(move->GetConectionValueTowardsNodeID(move->GetNodeIDOnListPosition(j)) + NodeSteps.GetConectionValueOnNodeID(move->GetID()), move->GetNodeIDOnListPosition(j), move->GetID());
				i = 1;
			}
			if (!NodeSteps.ExistedID(move->GetNodeIDOnListPosition(j))) {
				NodeSteps.AddConection(move->GetConectionValueTowardsNodeID(move->GetNodeIDOnListPosition(j)) + NodeSteps.GetConectionValueOnNodeID(move->GetID()), move->GetNodeIDOnListPosition(j), move->GetID());
			}
		}
		if (NodeSteps.GetConectionOnListPosition(i) == -1) {
			break;
		}
		move = graph->GetNodeWithID(NodeSteps.GetConectionOnListPosition(i));
	}
	Conection* ConectionMove = NodeSteps.GetStart();
	while (ConectionMove != nullptr) {
		std::cout << "\n";
		std::cout << "--(" << ConectionMove->GetValue() << ", ID:" << ConectionMove->GetID() << ")-->NodeID[" << ConectionMove->GetNodeID() << "]";
		ConectionMove = ConectionMove->GetNext();
	}
	return;
}


void Menus::PrintActual(Graph* graph) {
	if (graph->GetActualNode() == nullptr) {
		std::cout << "ERROR: There's No Actual Node" << std::endl;
		return;
	}
	if (graph->GetActualData() != nullptr) {
		std::cout << "Name:     " << ((Data*)graph->GetActualData())->name << std::endl;
		std::cout << "LastName: " << ((Data*)graph->GetActualData())->lastName << std::endl;
		std::cout << "Age:      " << ((Data*)graph->GetActualData())->age << std::endl;
		std::cout << "Reg:      " << ((Data*)graph->GetActualData())->reg << std::endl;
	}
	std::cout << "Node[content:" << graph->GetActualNode()->GetContent() << " | ID:" << graph->GetActualNode()->GetID() << "]";
}


void Menus::PrintEverything(Graph* graph) {
	if (graph->GetStartNode() == nullptr) {
		std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return;
	}
	Node* move = graph->GetStartNode();
	if (move == nullptr) {
		return;
	}
	while (move != nullptr) {
		std::cout << "Node[content:" << move->GetContent() << " | ID:" << move->GetID() << "]";
		std::cout << "\n";
		Conection* ConectionMove = move->GetConectionList()->GetStart();
		while (ConectionMove != nullptr) {
			std::cout << "\n";
			std::cout << "--(" << ConectionMove->GetValue() << ", ID:" << ConectionMove->GetID() << ")-->NodeID[" << ConectionMove->GetNodeID() << "]";
			ConectionMove = ConectionMove->GetNext();
		}
		std::cout << "\n*--------------------*\n";
		move = move->GetNext();
	}
}


void Menus::PrintWithNodeID(Graph* graph, int NodeID) {
	if (graph->GetStartNode() == nullptr) {
		std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return;
	}
	Node* move = graph->GetNodeWithID(NodeID);
	if (move == nullptr) {
		return;
	}
	if (graph->GetActualData() != nullptr) {
		std::cout << "Name:     " << ((Data*)move->GetData())->name << std::endl;
		std::cout << "LastName: " << ((Data*)move->GetData())->lastName << std::endl;
		std::cout << "Age:      " << ((Data*)move->GetData())->age << std::endl;
		std::cout << "Reg:      " << ((Data*)move->GetData())->reg << std::endl;
		Conection* ConectionMove = move->GetConectionList()->GetStart();
		while (ConectionMove != nullptr) {
			std::cout << "\n";
			std::cout << "--(" << ConectionMove->GetValue() << ", ID:" << ConectionMove->GetID() << ")-->NodeID[" << ConectionMove->GetNodeID() << "]";
			ConectionMove = ConectionMove->GetNext();
		}
		return;
	}
	if (move == nullptr) {
		std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
		return;
	}
	std::cout << "Node[content:" << move->GetContent() << " | ID:" << move->GetID() << "]";
}
