#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <map>
#include <string>
#include <vector>

#include "src/ck3_world/titles_importer.hpp"



namespace ck3_world
{

TEST(Ck3worldTitlesimporterTests, TitlesCanBeImported)
{
   const commonItems::ModFilesystem mod_filesystem("./test_files/Ck3worldTitlesimporterTests/TitlesCanBeImported", {});
   const std::map<std::filesystem::path, std::vector<std::string>> imported_titles = ImportTitles(mod_filesystem);

   EXPECT_THAT(imported_titles,
       testing::ElementsAre(testing::Pair("title_file_one.txt", std::vector<std::string>{"title_one", "title_two"}),
           testing::Pair("title_file_two.txt", std::vector<std::string>{"title_three", "title_four"})));
}

}  // namespace ck3_world