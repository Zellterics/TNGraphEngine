#include "Menus.h"

Menus::Menus(Graph* graph) {
	int content, NodeID;
	std::string stringContent;
	bool stop = false;
	std::string input;
	char filteredInput;
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
			std::cout << "---Terminate    ---\n";
			break;
		case 'a': case 'A':
			std::cout << "--->Node content:";
			std::cin >> stringContent;
			stringContent = CinFail(stringContent);
			graph->AddNode(stringContent);
			PrintActual(graph);
			break;
		case 'c': case 'C':
			std::cout << "--->Conection content:";
			std::cin >> stringContent;
			stringContent = CinFail(stringContent);
			std::cout << "\n--->Conection NodeID:";
			std::cin >> NodeID;
			NodeID = CinFail(NodeID);
			if(!graph->ConectToNodeID(stringContent, NodeID)){
				std::cout << "already connected" << std::endl;
			}
			PrintActual(graph);
			std::cout << "--(" << stringContent << ")-->";
			PrintWithNodeID(graph, NodeID);
			break;
		case 'g': case 'G':
			std::cout << "--->NodeID:";
			std::cin >> NodeID;
			NodeID = CinFail(NodeID);
			if (!graph->GoToNodeID(NodeID)) {
				std::cout << "--->ERROR: No Such NodeID\n";
			}
			PrintActual(graph);
			break;
		case 's': case 'S':
			std::cout << "--->NodeID:";
			std::cin >> NodeID;
			NodeID = CinFail(NodeID);
			if (!graph->MoveToNodeID(NodeID)) {
				std::cout << "--->ERROR: Not Such NodeID Conection\n";
			}
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
			std::cout << "--->Node content:";
			std::cin >> stringContent;
			stringContent = CinFail(stringContent);
			graph->ChangeActualNodeContent(stringContent);
			PrintActual(graph);
			break;
		case 'h': case 'H':
			std::cout << "There are " << graph->CountNodes() << " Nodes\n";
			break;
		default:
			std::cout << "That's Not An Option" << std::endl;
			break;
		}
		std::cout << "\n--->";
		std::cin >> input;
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
	if (graph->GetActualData() != nullptr) {
		while (move != nullptr) {
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
			std::cout << "\n*--------------------*\n";
			move = move->GetNext();
		}
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

//a pepe cacas 21 21100290 a paquito maya 21 21300 a juan alcachofas 10 21300290 a martin julian 17 21300490 a alejandro pinzon 17 211002