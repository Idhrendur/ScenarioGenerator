#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>

#include "src/output/ck3/output_titles.hpp"



namespace output
{

TEST(OutputCk3Outputtitles, TitlesCanBeOutput)
{
   std::filesystem::remove_all("OutputCk3Outputtitles/TitlesCanBeOutput");
   OutputCk3Titles("OutputCk3Outputtitles/TitlesCanBeOutput",
       {{"test_file_1.txt", {"test_title_one", "test_title_two"}},
           {"test_file_2.txt", {"test_title_three", "test_title_four"}}});

   std::ifstream title_file_one("output/OutputCk3Outputtitles/TitlesCanBeOutput/history/titles/test_file_1.txt");
   ASSERT_TRUE(title_file_one.is_open());
   std::stringstream title_file_one_stream;
   std::copy(std::istreambuf_iterator<char>(title_file_one),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(title_file_one_stream));
   title_file_one.close();

   EXPECT_EQ(title_file_one_stream.str(),
       "test_title_one = {\n"
       "  1.1.1 = {\n"
       "    government = herder_government\n"
       "    holder = 0\n"
       "  }\n"
       "}\n"
       "\n"
       "test_title_two = {\n"
       "  1.1.1 = {\n"
       "    government = herder_government\n"
       "    holder = 0\n"
       "  }\n"
       "}\n"
       "\n");

   std::ifstream title_file_two("output/OutputCk3Outputtitles/TitlesCanBeOutput/history/titles/test_file_2.txt");
   ASSERT_TRUE(title_file_two.is_open());
   std::stringstream title_file_two_stream;
   std::copy(std::istreambuf_iterator<char>(title_file_two),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(title_file_two_stream));
   title_file_two.close();

   EXPECT_EQ(title_file_two_stream.str(),
       "test_title_three = {\n"
       "  1.1.1 = {\n"
       "    government = herder_government\n"
       "    holder = 0\n"
       "  }\n"
       "}\n"
       "\n"
       "test_title_four = {\n"
       "  1.1.1 = {\n"
       "    government = herder_government\n"
       "    holder = 0\n"
       "  }\n"
       "}\n"
       "\n");
}


TEST(OutputCk3Outputtitles, BaroniesGetNoGovernment)
{
   std::filesystem::remove_all("OutputCk3Outputtitles/BaroniesGetNoGovernment");
   OutputCk3Titles("OutputCk3Outputtitles/BaroniesGetNoGovernment", {{"test_file.txt", {"b_test_title"}}});

   std::ifstream title_file("output/OutputCk3Outputtitles/BaroniesGetNoGovernment/history/titles/test_file.txt");
   ASSERT_TRUE(title_file.is_open());
   std::stringstream title_file_stream;
   std::copy(std::istreambuf_iterator<char>(title_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(title_file_stream));
   title_file.close();

   EXPECT_FALSE(title_file_stream.str().contains("government"));
}


TEST(OutputCk3Outputtitles, CountiesAndBaroniesGetWastelandHolders)
{
   std::filesystem::remove_all("OutputCk3Outputtitles/CountiesAndBaroniesGetWastelandHolders");
   OutputCk3Titles("OutputCk3Outputtitles/CountiesAndBaroniesGetWastelandHolders",
       {{"test_file.txt", {"c_test_title", "b_test_title"}}});

   std::ifstream title_file(
       "output/OutputCk3Outputtitles/CountiesAndBaroniesGetWastelandHolders/history/titles/test_file.txt");
   ASSERT_TRUE(title_file.is_open());
   std::stringstream title_file_stream;
   std::copy(std::istreambuf_iterator<char>(title_file),
       std::istreambuf_iterator<char>(),
       std::ostreambuf_iterator<char>(title_file_stream));
   title_file.close();

   EXPECT_EQ(title_file_stream.str(),
       "c_test_title = {\n"
       "  1.1.1 = {\n"
       "    government = herder_government\n"
       "    holder = wasteland_1\n"
       "  }\n"
       "}\n"
       "\n"
       "b_test_title = {\n"
       "  1.1.1 = {\n"
       "    holder = wasteland_2\n"
       "  }\n"
       "}\n"
       "\n");
}

}  // namespace output