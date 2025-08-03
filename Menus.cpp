#include "Menus.h"
#include "FileIO.h"
#include <fstream>
#include <unordered_map>
#include <filesystem>

Menus::Menus(Graph* graph) {
	this->graph = graph;
	std::ifstream file;
	int content, NodeID;
	std::string stringContent;
	bool stop = false;
	std::string input;
	std::string fileInput = "default.txt";
	char filteredInput;
	bool userInput = true;
	input = 'f';
	std::unordered_map<char, std::function<void()>> commands;
	commands['a'] = [&](){
		stringContent = GetInput(userInput, file);
		graph->AddNode(stringContent);
		if (userInput)
			PrintActual();
	};
	commands['i'] = [&](){
		stringContent = GetInput(userInput, file);
		if(graph->GetNodeByContent(stringContent)){
			return;
		}
		graph->GoToNodeID(graph->GetNodeByContent(stringContent)->GetID());
	};
	commands['c'] = [&](){
		stringContent = GetInput(userInput, file);
		input = GetInput(userInput, file);
		std::from_chars(input.data(), input.data() + input.size(), NodeID);
		if(!graph->ConectToNodeID(stringContent, NodeID)){
			std::cout << "already connected" << std::endl;
		}
		if (userInput){
			PrintActual();
			std::cout << "--(" << stringContent << ")-->";
			PrintWithNodeID(NodeID);
		}
	};
	commands['g'] = [&](){
		input = GetInput(userInput, file);
		std::from_chars(input.data(), input.data() + input.size(), NodeID);
		if (!graph->GoToNodeID(NodeID)) {
			std::cout << "--->ERROR: No Such NodeID\n";
		}
		if (userInput)
			PrintActual();
	};
	commands['s'] = [&](){
		input = GetInput(userInput, file);
		std::from_chars(input.data(), input.data() + input.size(), NodeID);
		if (!graph->MoveToNodeID(NodeID)) {
			std::cout << "--->ERROR: Not Such NodeID Conection\n";
		}
		if (userInput)
			PrintActual();
	};
	commands['p'] = [&](){
		PrintActual();
	};
	commands['e'] = [&](){
		PrintEverything();
	};
	commands['t'] = [&](){
		stop = true;
	};
	commands['b'] = [&](){
		{
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
	};
	commands['f'] = [&](){
		std::cout << "---FUNCTIONS    ---\n";
		std::cout << "---AddNode      ---\n";
		std::cout << "---ConectWith   ---\n";
		std::cout << "---GoTo         ---\n";
		std::cout << "---SlideTo      ---\n";
		std::cout << "---Print        ---\n";
		std::cout << "---Everything   ---\n";
		std::cout << "---BorderNodes  ---\n";
		std::cout << "---DeleteActual ---\n";
		std::cout << "---ModifyContent---\n";
		std::cout << "---HowManyNodes ---\n";
		std::cout << "---IdentifyNode ---\n";
		std::cout << "---LoadFromFile ---\n";
		std::cout << "---Next         ---\n";
		std::cout << "---UseAltMenu   ---\n";
		std::cout << "---Terminate    ---\n";
	};
	commands['d'] = [&](){
		graph->DeleteActual();
	};
	commands['m'] = [&](){
		stringContent = GetInput(userInput, file);
		graph->ChangeActualNodeContent(stringContent);
		if (userInput)
			PrintActual();
	};
	commands['h'] = [&](){
		std::cout << "There are " << graph->CountNodes() << " Nodes\n";
	};
	commands['l'] = [&](){
		std::cout << "File Path: ";
		std::getline(std::cin, fileInput);
		std::cout << fileInput;
		file = FileIO::GetFileInputStream(fileInput);
		
		if (!file.is_open()) {
			std::cout << "OOpsie: ewwow code: 004";
			return;
		}
		userInput = false;
	};
	commands['z'] = [&](){
		if(!userInput){
			userInput = true;
		}
	};

	while (!stop) {
		filteredInput = tolower(input[0]);
		if(filteredInput == 'n'){
			stop = true;
			break;
		}
		if(filteredInput == 'u'){
			break;
		}
		if(commands.contains(filteredInput)){
			commands[filteredInput]();
		} else {
			std::cout << "That's Not An Option" << std::endl;
		}
		if(userInput){
			std::cout << "\n--->";
		}
		input = GetInput(userInput, file);
	}
	
	while (!stop){
		stringContent = GetInput(userInput, file);
		stop = !AlternativeMenu(stringContent);
	}

	graph->GoToNodeID(0);
	std::string savedInputs = "";
	std::string folderName = FileIO::GetBaseFileName(fileInput);
	std::filesystem::path folderPath = FileIO::GetBasePath() / folderName;

	bool startLoadGamesMenu = true;
	if (!std::filesystem::exists(folderPath)) {
		startLoadGamesMenu = false;
	}
	std::vector<std::filesystem::path> saveFiles;
	if(startLoadGamesMenu){
		saveFiles = FileIO::GetGameSaveFiles(folderName);
		if (saveFiles.empty()) {
			startLoadGamesMenu = false;
		}
	}
	while (startLoadGamesMenu){
		std::string header = Out::CLEAR_SCREEN + Out::CURSOR_TOP_LEFT + Out::MoveCursorDown(8);
		std::cout << header << "L) Load Save File\n N) New Game\n -->";
		stringContent = GetInput();
		filteredInput = tolower(stringContent[0]);
		if(filteredInput == 'n'){
			break;
		}
		if(!filteredInput == 'l'){
			continue;
		}
		int selection = 0;
		while (true) {
			std::cout << header << "\t\tLoad Game For [" << folderName << "]\n";
			for (size_t i = 0; i < saveFiles.size(); ++i) {
				std::cout << "\t\t\t" << (i + 1) << " [" << FileIO::GetBaseFileName(saveFiles[i].string()) << "]\n";
			}
			std::cout << "\t\t\t\t[ ]\r\t\t\t\t[";

			stringContent = GetInput();
			auto [ptr, ec] = std::from_chars(stringContent.data(), stringContent.data() + stringContent.size(), selection);

			if (ec == std::errc() && selection >= 1 && selection <= (int)saveFiles.size()) {
				break;
			} else {
				std::cout << "\nInvalid Option. Input anything to retry\n";
				GetInput();
			}
		}
		
		std::filesystem::path saveFilePath = saveFiles[selection - 1];
		std::filesystem::path fullPath = folderPath / saveFilePath;
		if(file.is_open()){
			file.close();
			file.clear();
		}
		file = FileIO::GetFileInputStream(fullPath);
		int number;
		while (stringContent != "z") {
			stringContent = GetInput(false, file);
			if(stringContent == ""){
				stringContent = "1";
			}
			if(stringContent != "z"){
				savedInputs += stringContent + "\n";
			}
			auto [ptr, ec] = std::from_chars(stringContent.data(), stringContent.data() + stringContent.size(), number);
			if (ec == std::errc()) {
				graph->MoveToNodeID(graph->GetActualConections()->GetConectionOnListPosition(number));
			}
		}
		break;
	}
	StartGameLoop(savedInputs, fileInput);
	GetInput();
}

//Functions

void Menus::StartGameLoop(std::string& savedInputs, const std::string& fileInput){
	std::string input;
	int option = 0;
	int maxOption;
	std::string folderName = FileIO::GetBaseFileName(fileInput);
	std::string header = Out::CLEAR_SCREEN + Out::CURSOR_TOP_LEFT + Out::MoveCursorDown(8);
	std::string leftMenu = std::string("\t\t\t\t\t\t\t\t\t") + "E) Exit   S) Save";
	std::string dialog;
	while (true){
		graph->MoveToNodeID(graph->GetActualConections()->GetConectionOnListPosition(option));
		dialog = "\t\t" + graph->GetActualNode()->GetContent();
		std::cout << header << dialog << leftMenu << std::endl;
		if(graph->GetActualConections()->GetConectionOnListPosition(1) == -1){
			std::cout << std::endl << "---------------------------------------------------------------------------------------------------------";
			break;
		}
		if(graph->GetActualConections()->GetConectionOnListPosition(2) != -1){
			for (int i = 1; graph->GetActualConections()->GetConectionOnListPosition(i) != -1; i++){
				maxOption = i;
				std::cout << "\t\t\t" << i << "[ " << graph->GetActualConections()->GetConectionValueOnNodeID(graph->GetActualConections()->GetConectionOnListPosition(i)) << "]\n";
			}
			std::cout << "\t\t\t\t[ ]\r\t\t\t\t[";
		}else{
			maxOption = 1;
			std::cout << "\t\t-->";
		}
		std::getline(std::cin, input);
		input = CinFail(input);
		if(input[0] == 'e' || input[0] == 'E'){
			return;
		}
		if(input[0] == 's' || input[0] == 'S'){
			FileIO::CreateDirectories(folderName);
			savedInputs += "z";
			std::ofstream oFile = FileIO::GetFileOutputStream(fileInput);
			oFile.write(savedInputs.c_str(), savedInputs.size());
			savedInputs = savedInputs.substr(0, savedInputs.size() - 2);
			option = 0;
			std::cout << "\t\tGAME SAVED\n";
			GetInput();
			continue;
		}
		savedInputs += input + "\n";
		if (std::from_chars(input.data(), input.data() + input.size(), option).ec != std::errc()){
			option = 0;
		}
		if(maxOption == 1){
			option = 1;
			continue;
		}
		if (option > maxOption || option < 0){
			option = 0;
		}
	}
}

bool Menus::AlternativeMenu(std::string stringContent){
	std::string nodeName;
	std::string nodeName2;
	static std::unordered_map<std::string, int> nodeNameId;
	std::string conectionContent;
	if(stringContent == "start"){
		return false;
	}
	if(stringContent.find('[') == std::string::npos && stringContent.find('-') == std::string::npos){
		nodeName = stringContent;
		graph->AddNode("");
		nodeNameId.emplace(nodeName, graph->GetActualNode()->GetID());
		return true;
	}
	if(stringContent.find('[') < stringContent.find(' ')){
		nodeName = stringContent.substr(0, stringContent.find('['));
		stringContent = stringContent.substr(stringContent.find('['));

	} else {
		nodeName = stringContent.substr(0, stringContent.find(' '));
		stringContent = stringContent.substr(stringContent.find(' ') + 1);

	}
	if(!nodeNameId.contains(nodeName)){
		graph->AddNode(nodeName);

		nodeNameId.emplace(nodeName, graph->GetActualNode()->GetID());
		std::cout << stringContent << std::endl;
		if(stringContent[0] == '['){
			graph->GetActualNode()->SetContent(stringContent.substr(1, stringContent.find(']') - 1));
			stringContent = stringContent.substr(stringContent.find(']') + 1);
			nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
		} else {
			graph->GetActualNode()->SetContent("");
		}
	} else {
		graph->GoToNodeID(nodeNameId[nodeName]);
	}
	if(stringContent.size() == 0){
		return true;
	}
	if(stringContent[0] == '-' && stringContent[1] == '['){
		conectionContent = stringContent.substr(2, stringContent.find(']') - 2);
		stringContent = stringContent.substr(stringContent.find(']') + 4);
		nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
	} else {
		conectionContent = "";
	}
	if(stringContent.find('[') == std::string::npos){
		if(nodeNameId.contains(stringContent)){
			graph->ConectToNodeID(conectionContent, nodeNameId[stringContent]);
		} else {
			graph->AddNode("");

			nodeNameId.emplace(stringContent, graph->GetActualNode()->GetID());
			graph->GoToNodeID(nodeNameId[nodeName]);
			graph->ConectToNodeID(conectionContent, nodeNameId[nodeName]);
		}
		return true;
	}
	nodeName2 = stringContent.substr(0, stringContent.find('['));
	nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
	stringContent = stringContent.substr(stringContent.find('[') + 1);
	if(nodeNameId.contains(nodeName2)){
		graph->ConectToNodeID(conectionContent, nodeNameId[nodeName2]);

	} else {
		graph->AddNode(stringContent.substr(0, stringContent.find(']')));

		nodeNameId.emplace(nodeName2, graph->GetActualNode()->GetID());
		graph->GoToNodeID(nodeNameId[nodeName]);
		if (!nodeName2.empty() && nodeName2 != nodeName) {
			graph->ConectToNodeID(conectionContent, nodeNameId[nodeName2]);
		}


	}
	return true;
}

void Menus::PrintActual() {
	if (graph->GetActualNode() == nullptr) {
		std::cout << "ERROR: There's No Actual Node" << std::endl;
		return;
	}
	std::cout << "Node[content:" << graph->GetActualNode()->GetContent() << " | ID:" << graph->GetActualNode()->GetID() << "]";
}

std::string Menus::GetInput(bool userInput, std::ifstream &file){
	static std::string stringContent;
	if(userInput){
		std::getline(std::cin, stringContent);
	} else {
		if(!std::getline(file, stringContent)){
			std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
		}
	}
	stringContent = CinFail(stringContent);
	return stringContent;
}
std::string Menus::GetInput(){
	static std::string stringContent;
	std::getline(std::cin, stringContent);
	stringContent = CinFail(stringContent);
	return stringContent;
}

void Menus::PrintEverything() {
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

void Menus::PrintWithNodeID(int NodeID) {
	if (graph->GetStartNode() == nullptr) {
		std::cout << "ERROR: The Graph Is Empty" << std::endl;
		return;
	}
	Node* move = graph->GetNodeWithID(NodeID);
	if (move == nullptr) {
		std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
		return;
	}
	std::cout << "Node[content:" << move->GetContent() << " | ID:" << move->GetID() << "]";
}
