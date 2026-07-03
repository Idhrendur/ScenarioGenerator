#pragma once



#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <map>
#include <string>
#include <vector>



namespace ck3_world
{

std::map<std::string, std::vector<std::string>> ImportTitles(const commonItems::ModFilesystem& ck3_root);

}  // namespace ck3_world