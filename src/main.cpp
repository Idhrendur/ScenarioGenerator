#include <external/commonItems/Log.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <exception>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "src/ck3_world/county_capital_identifier.hpp"
#include "src/ck3_world/titles_importer.hpp"
#include "src/output/ck3/output_titles.hpp"



int main()
{
   try
   {
      const commonItems::ModFilesystem mod_filesystem(
          "C:/Program Files (x86)/Steam/steamapps/common/Crusader Kings III",
          {});
      const std::map<std::filesystem::path, std::vector<std::string>> titles = ck3_world::ImportTitles(mod_filesystem);
      const std::set<int> county_capitals = ck3_world::IdentifyCountyCapitals(mod_filesystem);
      output::OutputCk3Titles("test_mod", titles);
   }
   catch (std::exception& e)
   {
      Log(LogLevel::Error) << e.what();
   }
}