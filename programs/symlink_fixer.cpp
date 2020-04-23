#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile

#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

bool starts_with(std::string source, std::string string_to_find)
{
   return source.rfind(string_to_find, 0) == 0;
}

int main(int argc, char **argv)
{
   std::vector<std::string> filenames = {};
   for(auto& p: fs::recursive_directory_iterator("."))
   {
      if (fs::is_symlink(p))
      {
         filenames.push_back(p.path());
         std::string symlink_target = fs::read_symlink(p).string();
         std::string sanitized_target = symlink_target;
         if (starts_with(symlink_target, "/Users/markoates/Repos/"))
         {
            sanitized_target.replace(0, std::string("/Users/markoates/Repos/").length(), "../../../");
            std::cout << "!!!!!";
         }

         fs::remove(p.path());
         fs::create_symlink(sanitized_target, p.path());
         std::cout << p.path().string() << " -> " << sanitized_target << '\n';
      }
   }
}
