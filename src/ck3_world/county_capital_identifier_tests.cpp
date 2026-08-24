#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <set>

#include "src/ck3_world/county_capital_identifier.hpp"



namespace ck3_world
{

TEST(Ck3worldCountyCapitalIdentifierTests, CountyCapitalsCanBeIdentified)
{
   const commonItems::ModFilesystem mod_filesystem(
       "./test_files/Ck3worldCountyCapitalIdentifierTests/CountyCapitalsCanBeIdentified",
       {});
   const std::set<int> county_capitals = IdentifyCountyCapitals(mod_filesystem);

   EXPECT_THAT(county_capitals, testing::ElementsAre(1, 3, 5));
}

}  // namespace ck3_world