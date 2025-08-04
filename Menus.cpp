#include "Menus.h"
#include "FileIO.h"
#include <unordered_map>

Menus::Menus(Graph* graph) {
	this->graph = graph;
	commands['a'] = [&](){
		PrintIfUserInput(userInput, "--->Node content:");
		std::string content = GetInput(userInput, historyFile);
		this->graph->AddNode(content);
		if (userInput)
			PrintActual();
	};
	commands['i'] = [&](){
		PrintIfUserInput(userInput, "--->Node content:");
		std::string content = GetInput(userInput, historyFile);
		if(!this->graph->GetNodeByContent(content)){
			std::cout << "--->ERROR: No Such Node Content\n";
			return;
		}
		this->graph->GoToNodeID(this->graph->GetNodeByContent(content)->GetID());
		if(userInput)
			PrintActual();
	};
	commands['c'] = [&](){
		PrintIfUserInput(userInput, "--->Connection content:");
		std::string content = GetInput(userInput, historyFile);
		PrintIfUserInput(userInput, "--->Connect to NodeID:");
		std::string tempNodeId = GetInput(userInput, historyFile);
		int NodeID;
		if(std::from_chars(tempNodeId.data(), tempNodeId.data() + tempNodeId.size(), NodeID).ec != std::errc()){
			std::cout << "invalid ID";
			return;
		}
		if(!this->graph->ConectToNodeID(content, NodeID)){
			std::cout << "Error Conecting" << std::endl;
			return;
		}
		if (userInput){
			PrintActual();
			std::cout << "--(" << content << ")-->";
			PrintWithNodeID(NodeID);
		}
		PrintIfUserInput(userInput, "--(" + content + ")-->");
	};
	commands['g'] = [&](){
		PrintIfUserInput(userInput, "--->NodeID:");
		std::string tempNodeId = GetInput(userInput, historyFile);
		int NodeID;
		auto ec = std::from_chars(tempNodeId.data(), tempNodeId.data() + tempNodeId.size(), NodeID).ec;
		if (!(ec == std::errc()) || !this->graph->GoToNodeID(NodeID)) {
			std::cout << "--->ERROR: No Such NodeID\n";
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
	commands['b'] = [&](){
		{
		ConectionsList* erase = this->graph->GetActualConections();
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
	};
	commands['d'] = [&](){
		this->graph->DeleteActual();
	};
	commands['m'] = [&](){
		PrintIfUserInput(userInput, "--->Node content:");
		std::string content = GetInput(userInput, historyFile);
		this->graph->ChangeActualNodeContent(content);
		if (userInput)
			PrintActual();
	};
	commands['h'] = [&](){
		std::cout << "There are " << this->graph->CountNodes() << " Nodes\n";
	};
	commands['l'] = [&](){
		if(!userInput){
			std::cout << "WOW, You're already a file man, watchu doin?, okay okay, maybe you want to change to other config file.... I'll think about it\n";
			return;
		}
		std::cout << "File Path: ";
		fileInput = GetInput();
		std::cout << fileInput;
		historyFile = FileIO::GetFileInputStream(fileInput);
		
		if (!historyFile.is_open()) {
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
}

//Functions

void Menus::StartGameLoop(){
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
		if(input == ""){
			if(maxOption == 1){
				option = 1;
				savedInputs += "1\n";
				continue;
			}
			option = 0;
			continue;
		}
		if(input[0] == 'e' || input[0] == 'E'){
			return;
		}
		if(input[0] == 's' || input[0] == 'S'){
			FileIO::CreateDirectories(folderName);
			std::ofstream oFile = FileIO::GetFileOutputStream(fileInput);
			oFile << savedInputs << "z\n";
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

bool Menus::AlternativeMenu(){
	std::string nodeName;
	std::string nodeName2;
	static std::unordered_map<std::string, int> nodeNameId;
	std::string conectionContent;
	std::string commandLine;
	while (true){
		commandLine = GetInput(userInput, historyFile);
		if(commandLine == "start"){
			break;
		}
		if(commandLine.find('[') == std::string::npos && commandLine.find('-') == std::string::npos){
			nodeName = commandLine;
			graph->AddNode("");
			nodeNameId.emplace(nodeName, graph->GetActualNode()->GetID());
			continue;
		}
		if(commandLine.find('[') < commandLine.find(' ')){
			nodeName = commandLine.substr(0, commandLine.find('['));
			commandLine = commandLine.substr(commandLine.find('['));

		} else {
			nodeName = commandLine.substr(0, commandLine.find(' '));
			commandLine = commandLine.substr(commandLine.find(' ') + 1);

		}
		if(!nodeNameId.contains(nodeName)){
			graph->AddNode(nodeName);
			nodeNameId.emplace(nodeName, graph->GetActualNode()->GetID());
			if(commandLine[0] == '['){
				graph->GetActualNode()->SetContent(commandLine.substr(1, commandLine.find(']') - 1));
				commandLine = commandLine.substr(commandLine.find(']') + 1);
				nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
			} else {
				graph->GetActualNode()->SetContent("");
			}
		} else {
			graph->GoToNodeID(nodeNameId[nodeName]);
		}
		if(commandLine.size() == 0){
			continue;
		}
		if(commandLine[0] == '-' && commandLine[1] == '['){
			conectionContent = commandLine.substr(2, commandLine.find(']') - 2);
			commandLine = commandLine.substr(commandLine.find(']') + 4);
			nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
		} else {
			conectionContent = "";
		}
		if(commandLine.find('[') == std::string::npos){
			if(nodeNameId.contains(commandLine)){
				graph->ConectToNodeID(conectionContent, nodeNameId[commandLine]);
			} else {
				graph->AddNode("");

				nodeNameId.emplace(commandLine, graph->GetActualNode()->GetID());
				graph->GoToNodeID(nodeNameId[nodeName]);
				graph->ConectToNodeID(conectionContent, nodeNameId[nodeName]);
			}
			continue;
		}
		nodeName2 = commandLine.substr(0, commandLine.find('['));
		nodeName2.erase(0, nodeName2.find_first_not_of(" \t>-"));
		commandLine = commandLine.substr(commandLine.find('[') + 1);
		if(nodeNameId.contains(nodeName2)){
			graph->ConectToNodeID(conectionContent, nodeNameId[nodeName2]);

		} else {
			graph->AddNode(commandLine.substr(0, commandLine.find(']')));

			nodeNameId.emplace(nodeName2, graph->GetActualNode()->GetID());
			graph->GoToNodeID(nodeNameId[nodeName]);
			if (!nodeName2.empty() && nodeName2 != nodeName) {
				graph->ConectToNodeID(conectionContent, nodeNameId[nodeName2]);
			}


		}
	}
	PrintIfUserInput(userInput, "Input Start Node Name, Default/Invalid = ID(0): ");
	std::string startNodeName = GetInput(userInput, historyFile);
	graph->GoToNodeID(0);
	graph->GoToNodeID(nodeNameId[startNodeName]);
	return true;
}

void Menus::LegacyMenu(){
	char filteredInput;
	std::string input = "f";
	while (true) {
		filteredInput = tolower(input[0]);
		if(filteredInput == 'n'){
			break;
		}
		if(filteredInput == 'u'){
			AlternativeMenu();
			break;
		}
		if(commands.contains(filteredInput)){
			commands[filteredInput]();
		} else {
			std::cout << "That's Not An Option" << std::endl;
		}
		PrintIfUserInput(userInput, "-->");
		input = GetInput(userInput, historyFile);
	}
	if(historyFile.is_open()){
		historyFile.close();
		historyFile.clear();
	}
}

void Menus::LoadGamesMenu(){
	savedInputs = "";
	saveFiles = GetFolderSaveFiles(FileIO::GetBaseFileName(fileInput));
	if(!saveFiles.size()){
		std::cout << "dsaaaaaaaaaaa " + fileInput;
		return;
	}
	std::string folderName = FileIO::GetBaseFileName(fileInput);
	while (true){
		std::string header = Out::CLEAR_SCREEN + Out::CURSOR_TOP_LEFT + Out::MoveCursorDown(8);
		std::cout << header << "L) Load Save File\n N) New Game\n -->";
		std::string commandLine = GetInput();
		char filteredInput = tolower(commandLine[0]);
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

			commandLine = GetInput();
			auto [ptr, ec] = std::from_chars(commandLine.data(), commandLine.data() + commandLine.size(), selection);

			if (ec == std::errc() && selection >= 1 && selection <= (int)saveFiles.size()) {
				break;
			} else {
				std::cout << "\nInvalid Option. Input anything to retry\n";
				GetInput();
			}
		}
		
		std::filesystem::path saveFilePath = saveFiles[selection - 1];
		std::filesystem::path fullPath = FileIO::GetBasePath() / folderName / saveFilePath;
		
		std::ifstream file = FileIO::GetFileInputStream(fullPath);
		int number;
		while (commandLine != "z") {
			commandLine = GetInput(false, file);
			if(commandLine == ""){
				commandLine = "1";
			}
			if(commandLine != "z"){
				savedInputs += commandLine + "\n";
			}
			auto [ptr, ec] = std::from_chars(commandLine.data(), commandLine.data() + commandLine.size(), number);
			if (ec == std::errc()) {
				graph->MoveToNodeID(graph->GetActualConections()->GetConectionOnListPosition(number));
			}
		}
		break;
	}
}

void Menus::PrintActual() {
	if (graph->GetActualNode() == nullptr) {
		std::cout << "ERROR: There's No Actual Node" << std::endl;
		return;
	}
	std::cout << "Node[content:" << graph->GetActualNode()->GetContent() << " | ID:" << graph->GetActualNode()->GetID() << "]";
}

void Menus::PrintIfUserInput(bool userInput, std::string stringContent){
	if(userInput){
		std::cout << stringContent;
	}
}

std::string Menus::GetInput(bool userInput, std::ifstream &file){
	std::string stringContent;
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

std::vector<std::filesystem::path> Menus::GetFolderSaveFiles(std::string folderName){
	std::filesystem::path folderPath = FileIO::GetBasePath() / folderName;
	if (!std::filesystem::exists(folderPath)) {
		return {};
	}
	std::vector<std::filesystem::path> saveFiles;
		saveFiles = FileIO::GetGameSaveFiles(folderName);
	return saveFiles;
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
