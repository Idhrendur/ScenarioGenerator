#pragma once


#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <set>



namespace ck3_world
{

std::set<int> IdentifyCountyCapitals(const commonItems::ModFilesystem& ck3_root);

}  // namespace ck3_world