#include "src/output/ck3/output_titles.hpp"

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>



namespace output
{

void OutputCk3Titles(const std::filesystem::path& output_name,
    const std::map<std::filesystem::path, std::vector<std::string>>& ck3_titles)
{
   const std::filesystem::path titles_path = "output" / output_name / "history/titles";
   std::filesystem::create_directories(titles_path);

   int holder_num = 1;
   for (const auto& [filename, titles]: ck3_titles)
   {
      const std::filesystem::path title_filename = titles_path / filename;
      std::ofstream titles_file(title_filename);
      if (!titles_file.is_open())
      {
         throw std::runtime_error(fmt::format("Could not open {}", title_filename.string()));
      }

      for (const std::string& title: titles)
      {
         fmt::println(titles_file, "{} = {{", title);
         fmt::println(titles_file, "  1.1.1 = {{");
         if (!title.starts_with('b'))
         {
            fmt::println(titles_file, "    government = herder_government");
         }
         if (title.starts_with('c') || title.starts_with('b'))
         {
            fmt::println(titles_file, "    holder = wasteland_{}", holder_num);
            ++holder_num;
         }
         else
         {
            fmt::println(titles_file, "    holder = 0");
         }
         fmt::println(titles_file, "  }}");
         fmt::println(titles_file, "}}");
         fmt::println(titles_file, "");
      }
   }
}

}  // namespace output