#pragma once



#include <filesystem>
#include <map>
#include <string>
#include <vector>



namespace output
{

void OutputCk3Titles(const std::filesystem::path& output_name,
    const std::map<std::filesystem::path, std::vector<std::string>>& ck3_titles);

}  // namespace output