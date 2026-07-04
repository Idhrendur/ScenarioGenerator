#include "src/ck3_world/titles_importer.hpp"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/Log.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/Parser.h>
#include <external/commonItems/ParserHelpers.h>
#include <fmt/format.h>

#include <cstdio>
#include <filesystem>
#include <istream>
#include <map>
#include <string>
#include <vector>



namespace ck3_world
{

std::map<std::filesystem::path, std::vector<std::string>> ImportTitles(const commonItems::ModFilesystem& ck3_root)
{
   std::map<std::filesystem::path, std::vector<std::string>> titles;
   size_t num_titles = 0;

   std::vector<std::string> titles_in_file;

   commonItems::parser file_parser;
   file_parser.registerRegex(commonItems::catchallRegex,
       [&titles_in_file](const std::string& title, std::istream& stream) {
          titles_in_file.push_back(title);
          commonItems::ignoreItem("", stream);
       });

   for (const auto& file: ck3_root.GetAllFilesInFolder("game/history/titles"))
   {
      titles_in_file.clear();

      file_parser.parseFile(file);
      num_titles += titles_in_file.size();
      titles.emplace(file.filename(), titles_in_file);
   }

   Log(LogLevel::Info) << fmt::format("Imported {} titles in {} files.", num_titles, titles.size());
   return titles;
}


}  // namespace ck3_world
