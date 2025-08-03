#include "FileIO.h"

std::string FileIO::GetBaseFileName(const std::string& fileInput){
    size_t pos = fileInput.find_last_of('.');
    return pos == std::string::npos ? fileInput : fileInput.substr(0, pos);
}

std::filesystem::path FileIO::GetBasePath(){
    #ifdef _WIN32
        const char* appdata = std::getenv("APPDATA");
        if (appdata) {
            return std::filesystem::path(appdata) / "TNGraphEngine";
        } else {
            return "saves";
        }
    #else
        return "saves";
    #endif
}

std::ofstream FileIO::GetFileOutputStream(const std::string& folderName){
    std::filesystem::path saveDir = GetBasePath() / GetBaseFileName(folderName);

    std::filesystem::create_directories(saveDir);

    std::filesystem::path fileName = "savefile.tng";
    std::filesystem::path fullPath = saveDir / fileName;

    int counter = 1;
    while (std::filesystem::exists(fullPath)) {
        fileName = "savefile (" + std::to_string(counter++) + ").tng";
        fullPath = saveDir / fileName;
    }

    std::ofstream oFile(fullPath);
    if (!oFile.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + fullPath.string());
    }
    return oFile;
}

std::ifstream FileIO::GetFileInputStream(const std::filesystem::path& filePath){
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Archivo no encontrado: " + filePath.string());
    }
    return file;
}

std::vector<std::filesystem::path> FileIO::GetGameSaveFiles(const std::string& folderName){
    std::filesystem::path folderFullPath = GetBasePath() / folderName;
    std::vector<std::filesystem::path> saveFiles;
    for (const auto& entry : std::filesystem::directory_iterator(folderFullPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".tng") {
            saveFiles.push_back(entry.path().filename().string());
        }
    }
    return saveFiles;
}

bool FileIO::CreateDirectories(const std::string& folderName){
    std::filesystem::path folderFullPath = GetBasePath() / folderName;
    return std::filesystem::create_directories(folderFullPath);
}