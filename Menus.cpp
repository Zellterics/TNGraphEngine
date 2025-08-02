#include "Menus.h"
#include <fstream>
#include <unordered_map>
#include <filesystem>

Menus::Menus(Graph* graph) {
	std::ifstream file;
	int content, NodeID;
	std::string stringContent;
	bool stop = false;
	std::string input;
	std::string fileInput = "default.txt";
	char filteredInput;
	bool userInput = true;
	input = 'f';
	while (!stop) {
		filteredInput = input[0];
		if(filteredInput == 'N' || filteredInput == 'n'){
			stop = true;
			break;
		}
		if(filteredInput == 'u' || filteredInput == 'U'){
			stop = false;
			break;
		}
		switch (filteredInput) {
		case 'f': case 'F':
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
			break;
		case 'i': case 'I':
			if(userInput){
				std::cout << "--->Node content:";
				std::getline(std::cin, stringContent);
			} else {
				if(!std::getline(file, stringContent)){
					std::cerr << "OOpsie: ewwow code: 005 -> reading file" << std::endl;
				}
			}
			stringContent = CinFail(stringContent);
			if(graph->GetNodeByContent(stringContent)){
				break;
			}
			graph->GoToNodeID(graph->GetNodeByContent(stringContent)->GetID());
			break;
		case 'a': case 'A':
			if(userInput){
				std::cout << "--->Node content:";
				std::getline(std::cin, stringContent);
			} else {
				if(!std::getline(file, stringContent)){
					std::cerr << "OOpsie: ewwow code: 012 -> reading file" << std::endl;
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
					std::cerr << "OOpsie: ewwow code: 011 -> reading file" << std::endl;
				}
			}
			stringContent = CinFail(stringContent);
			if(userInput){
				std::cout << "--->Conection NodeID:";
				std::cin >> NodeID;
				NodeID = CinFail(NodeID);
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 010 -> reading file" << std::endl;
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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 009 -> reading file" << std::endl;
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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else {
				std::string save;
				if(!std::getline(file, save)){
					std::cerr << "OOpsie: ewwow code: 008 -> reading file" << std::endl;
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
					std::cerr << "OOpsie: ewwow code: 007 -> reading file" << std::endl;
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
			std::getline(std::cin, fileInput);
			std::cout << fileInput;
			file = std::ifstream(fileInput);
			
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
				std::cerr << "OOpsie: ewwow code: 006 -> reading file" << std::endl;
			}
		}
	}
	
	while (!stop){
		stringContent = UserInput(userInput, file);
		stop = !AlternativeMenu(graph, stringContent);
		
		// A[test1]
		// A --> B[test2]
		// A -[label1]-> C[test3]
		// B -[label2]-> B
		// D
		// D --> E
		// F[test4] --> G
		// G -[label3]-> H[test con espacios]
		// start
	}

	int option = 0;
	graph->GoToNodeID(option);
	int maxOption;
	std::string savedInputs = "";

	std::string baseName = fileInput.substr(0, fileInput.find_last_of('.'));
	std::string folderPath;
	#ifdef _WIN32
		const char* appdata = std::getenv("APPDATA");
		if (appdata) {
			folderPath = std::string(appdata) + "\\TNGraphEngine\\" + baseName;
		} else {
			folderPath = "saves\\" + baseName;
		}
	#else
		folderPath = "saves/" + baseName;
	#endif

	bool startLoadGamesMenu = true;
	if (!std::filesystem::exists(folderPath)) {
		std::cout << "No existe la carpeta de saves: " << folderPath << "\n";
		// opcional: std::filesystem::create_directories(folderPath);
		startLoadGamesMenu = false;
	}
	std::vector<std::string> saveFiles;
	if(startLoadGamesMenu){
		for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".tng") {
				saveFiles.push_back(entry.path().filename().string());
			}
		}
		if (saveFiles.empty()) {
			startLoadGamesMenu = false;
		}
	}
	while (startLoadGamesMenu){
		std::cout << "\033[2J\033[H L) Load Save File\n N) New Game\n -->";
		stringContent = UserInput(true, file);
		if(stringContent[0] == 'n' || stringContent[0] == 'N'){
			break;
		}
		if(stringContent[0] == 'l' || stringContent[0] == 'L'){
			int selection = 0;
			while (true) {
				std::cout << "\033[2J\033[H\033[<8>B\t\tLoad Game For [" << baseName << "]\n";
				for (size_t i = 0; i < saveFiles.size(); ++i) {
					std::string nameWithoutExt = saveFiles[i].substr(0, saveFiles[i].find_last_of('.'));
					std::cout << "\t\t\t" << (i + 1) << " [" << nameWithoutExt << "]\n";
				}
				std::cout << "\t\t\t\t[ ]\r\t\t\t\t[";

				stringContent = UserInput(true, file);
				auto [ptr, ec] = std::from_chars(stringContent.data(), stringContent.data() + stringContent.size(), selection);

				if (ec == std::errc() && selection >= 1 && selection <= (int)saveFiles.size()) {
					break;
				} else {
					std::cout << "\nInvalid Option. Input anything to retry\n";
					UserInput(true, file);
				}
			}
			
			std::string saveFile = saveFiles[selection - 1];
			std::string fullPath;
			#ifdef _WIN32
				fullPath = folderPath + "\\" + saveFile;
			#else
				fullPath = folderPath + "/" + saveFile;
			#endif
			if(file.is_open()){
				file.close();
			}
			file = std::ifstream(fullPath);
			if (!file.is_open()) {
				std::cout << "OOpsie: ewwow code: 012 -> failed to open file\n";
				UserInput(true, file);
				continue;
			}
			int number;
			while (stringContent != "z") {
				stringContent = UserInput(false, file);
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
	}
	

	option = 0;
	stop = false;
	
	while (!stop){
		graph->MoveToNodeID(graph->GetActualConections()->GetConectionOnListPosition(option));
		std::cout << "\033[2J\033[H\033[<8>B\t\t" << graph->GetActualNode()->GetContent() << "\t\t\t\t\t\t\t\t\t" << "E) Exit   S) Save" << std::endl;
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
			baseName = fileInput.substr(0, fileInput.find_last_of('.'));
			#ifdef _WIN32
				const char* appdata = std::getenv("APPDATA");
				if (appdata) {
					folderPath = std::string(appdata) + "\\TNGraphEngine\\" + baseName;
				} else {
					folderPath = "saves\\" + baseName;
				}
			#else
				folderPath = "saves/" + baseName;
			#endif
			std::filesystem::create_directories(folderPath);
			savedInputs += "z";
			std::ofstream oFile = getSaveFileStream(fileInput);
			oFile.write(savedInputs.c_str(), savedInputs.size());
			savedInputs = savedInputs.substr(0, savedInputs.size() - 2);
			option = 0;
			std::cout << "\t\tGAME SAVED\n";
			UserInput(true, file);
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
	std::cin >> stringContent;
}

//Functions

bool Menus::AlternativeMenu(Graph* graph, std::string stringContent){
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

std::ofstream Menus::getSaveFileStream(const std::string& fileInput) {
    std::string baseName;
    size_t lastDot = fileInput.find_last_of(".");
    if (lastDot != std::string::npos) {
        baseName = fileInput.substr(0, lastDot);
    } else {
        baseName = fileInput;
    }

    std::string saveDir;

    #ifdef _WIN32
        const char* appdata = std::getenv("APPDATA");
        if (appdata) {
            saveDir = std::string(appdata) + "\\TNGraphEngine\\" + baseName;
        } else {
            saveDir = "saves\\" + baseName;
        }
    #else
        saveDir = "saves/" + baseName;
    #endif

    std::filesystem::create_directories(saveDir);

    std::string filename = "savefile.tng";
    std::string fullPath = saveDir + "/" + filename;

    int counter = 1;
    while (std::filesystem::exists(fullPath)) {
        filename = "savefile (" + std::to_string(counter++) + ").tng";
        fullPath = saveDir + "/" + filename;
    }

    std::ofstream oFile(fullPath);
    return oFile;
}

void Menus::PrintActual(Graph* graph) {
	if (graph->GetActualNode() == nullptr) {
		std::cout << "ERROR: There's No Actual Node" << std::endl;
		return;
	}
	std::cout << "Node[content:" << graph->GetActualNode()->GetContent() << " | ID:" << graph->GetActualNode()->GetID() << "]";
}

std::string Menus::UserInput(bool userInput, std::ifstream &file){
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
	if (move == nullptr) {
		std::cout << "ERROR: Node " << NodeID << " Doesn't Exists" << std::endl;
		return;
	}
	std::cout << "Node[content:" << move->GetContent() << " | ID:" << move->GetID() << "]";
}
