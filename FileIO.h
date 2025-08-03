#pragma once
#include <filesystem>
#include <vector>
#include <fstream>

namespace FileIO{
    std::string GetBaseFileName(const std::string& fileInput);
    std::ofstream GetFileOutputStream(const std::string& folderName);
    std::ifstream GetFileInputStream(const std::filesystem::path& filePath);
    std::vector<std::filesystem::path> GetGameSaveFiles(const std::string& folderName);
    bool CreateDirectories(const std::string& folderName);
    std::filesystem::path GetBasePath();
}