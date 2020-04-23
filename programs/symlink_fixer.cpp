#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile

#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iterator>
#include <sstream>

#include <Blast/ShellCommandExecutorWithCallback.hpp>

namespace fs = std::filesystem;

bool starts_with(std::string source, std::string string_to_find)
{
   return source.rfind(string_to_find, 0) == 0;
}

int line_count(std::string filename) // this function is untested
{
   std::ifstream myfile(filename);

   // new lines will be skipped unless we stop it from happening:    
   myfile.unsetf(std::ios_base::skipws);

   // count the newlines with an algorithm specialized for counting:
   unsigned line_count = std::count(
         std::istream_iterator<char>(myfile),
         std::istream_iterator<char>(), 
         '\n');

   //std::cout << "Lines: " << line_count << "\n";}
   return line_count;
}

bool likely_an_intended_symlink(std::string filename, std::string string_to_find)
{
   std::ifstream infile("test.txt");
   bool starts_with_string = false;

   if (infile.good())
   {
      std::string sLine;
      getline(infile, sLine);
      //std::cout << sLine << std::endl;
      if (starts_with(sLine, string_to_find)) starts_with_string = true;
      if (starts_with(sLine, "../") && line_count(filename) == 1) starts_with_string = true;
   }

   infile.close();

   return starts_with_string;
}

int main(int argc, char **argv)
{
   const std::string MAGIC_STRING = "/Users/markoates/Repos/";
   std::vector<std::string> filenames = {};
   for(auto& p: fs::recursive_directory_iterator("."))
   {
      std::cout << p.path().string() << std::endl;

      if (fs::is_symlink(p) || likely_an_intended_symlink(p.path().string(), MAGIC_STRING))
      {
         std::string filename = p.path().string();
         std::replace(filename.begin(), filename.end(), '\\', '/');
         filenames.push_back(filename);
         std::string symlink_target = fs::read_symlink(p).string();
         std::string sanitized_target = symlink_target;
         if (starts_with(symlink_target, MAGIC_STRING))
         {
            // this means it's a hard-coded target path
            // TODO: make this ../../../ instead count the proper number of "../" elements to prefix
            sanitized_target.replace(0, std::string(MAGIC_STRING).length(), "../../../");
            std::cout << "!!!!!";
         }

         fs::remove(p.path());
         try
         {
            fs::create_symlink(sanitized_target, p.path());
         }
         catch (const std::exception& e)
         {
            std::cout << "Caught error when attempting to fs::create_symlink: " << e.what() << std::endl;
            std::cout << "Attempting alternative link creation with shell command" << std::endl;

            std::stringstream command;
            command << "ln -s " << sanitized_target << " " << filename;
            Blast::ShellCommandExecutorWithCallback executor(command.str());
            executor.execute();
            //create_symlink(sanitized_target, p.path());

            //p.path().string() << " -> " << sanitized_target << '\n';
            //error
         }
         std::cout << p.path().string() << " -> " << sanitized_target << '\n';
      }
   }
}
