#include "src/ck3_world/county_capital_identifier.hpp"

#include <external/commonItems/Log.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/Parser.h>
#include <external/commonItems/ParserHelpers.h>

#include <format>
#include <istream>
#include <set>



namespace ck3_world
{

std::set<int> IdentifyCountyCapitals(const commonItems::ModFilesystem& ck3_root)
{
   std::set<int> county_capitals;

   commonItems::parser barony_parser;
   barony_parser.registerKeyword("province", [&county_capitals](std::istream& input) {
      county_capitals.emplace(commonItems::getInt(input));
   });
   barony_parser.IgnoreUnregisteredItems();

   commonItems::parser county_parser;
   bool found_a_barony = false;
   county_parser.registerRegex("b_.*", [&barony_parser, &found_a_barony](const std::string&, std::istream& input) {
      if (found_a_barony)
      {
         commonItems::ignoreItem("", input);
      }
      else
      {
         barony_parser.parseStream(input);
         found_a_barony = true;
      }
   });
   county_parser.IgnoreUnregisteredItems();

   commonItems::parser duchy_parser;
   duchy_parser.registerRegex("c_.*", [&county_parser, &found_a_barony](const std::string&, std::istream& input) {
      found_a_barony = false;
      county_parser.parseStream(input);
   });
   duchy_parser.IgnoreUnregisteredItems();

   commonItems::parser kingdom_parser;
   kingdom_parser.registerRegex("d_.*", [&duchy_parser](const std::string&, std::istream& input) {
      duchy_parser.parseStream(input);
   });
   kingdom_parser.registerRegex("c_.*", [&county_parser](const std::string&, std::istream& input) {
      county_parser.parseStream(input);
   });
   kingdom_parser.IgnoreUnregisteredItems();

   commonItems::parser empire_parser;
   empire_parser.registerRegex("k_.*", [&kingdom_parser](const std::string&, std::istream& input) {
      kingdom_parser.parseStream(input);
   });
   empire_parser.registerRegex("d_.*", [&duchy_parser](const std::string&, std::istream& input) {
      duchy_parser.parseStream(input);
   });
   empire_parser.registerRegex("c_.*", [&county_parser](const std::string&, std::istream& input) {
      county_parser.parseStream(input);
   });
   empire_parser.IgnoreUnregisteredItems();

   commonItems::parser hegemony_parser;
   hegemony_parser.registerRegex("e_.*", [&empire_parser](const std::string&, std::istream& input) {
      empire_parser.parseStream(input);
   });
   hegemony_parser.registerRegex("k_.*", [&kingdom_parser](const std::string&, std::istream& input) {
      kingdom_parser.parseStream(input);
   });
   hegemony_parser.registerRegex("d_.*", [&duchy_parser](const std::string&, std::istream& input) {
      duchy_parser.parseStream(input);
   });
   hegemony_parser.registerRegex("c_.*", [&county_parser](const std::string&, std::istream& input) {
      county_parser.parseStream(input);
   });
   hegemony_parser.IgnoreUnregisteredItems();

   commonItems::parser file_parser;
   file_parser.registerRegex("h_.*", [&hegemony_parser](const std::string&, std::istream& input) {
      hegemony_parser.parseStream(input);
   });
   file_parser.registerRegex("e_.*", [&empire_parser](const std::string&, std::istream& input) {
      empire_parser.parseStream(input);
   });
   file_parser.registerRegex("k_.*", [&kingdom_parser](const std::string&, std::istream& input) {
      kingdom_parser.parseStream(input);
   });
   file_parser.registerRegex("d_.*", [&duchy_parser](const std::string&, std::istream& input) {
      duchy_parser.parseStream(input);
   });
   file_parser.registerRegex("c_.*", [&county_parser](const std::string&, std::istream& input) {
      county_parser.parseStream(input);
   });
   file_parser.IgnoreUnregisteredItems();

   for (const auto& file: ck3_root.GetAllFilesInFolder("game/common/landed_titles"))
   {
      if (file.extension() != ".txt")
      {
         continue;
      }
      file_parser.parseFile(file);
   }

   Log(LogLevel::Info) << std::format("Identified {} capitals", county_capitals.size());
   return county_capitals;
}

}  // namespace ck3_world