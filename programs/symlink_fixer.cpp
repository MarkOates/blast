#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile

#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
   std::vector<std::string> filenames = {};
   for(auto& p: fs::recursive_directory_iterator("."))
   {
      if (fs::is_symlink(p))
      {
         filenames.push_back(p.path());
         std::string symlink_target = fs::read_symlink(p);
         std::cout << p.path().string() << " -> " << symlink_target << '\n';
      }
   }
}
