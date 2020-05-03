

#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <filesystem>


namespace Blast
{
namespace Project
{


ProjectSymlinkFixer::ProjectSymlinkFixer(std::string project_folder)
   : project_folder(project_folder)
{
}


ProjectSymlinkFixer::~ProjectSymlinkFixer()
{
}


std::string ProjectSymlinkFixer::get_project_folder()
{
   return project_folder;
}


bool ProjectSymlinkFixer::starts_with(std::string source, std::string string_to_find)
{
return source.rfind(string_to_find, 0) == 0;

}

int ProjectSymlinkFixer::line_count(std::string filename)
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

std::string ProjectSymlinkFixer::read_file_firstline(std::string filename)
{
std::ifstream infile(filename);

std::string sLine;
if (infile.good())
{
   getline(infile, sLine);
}
else
{
   throw std::runtime_error("Unexpected error in read_file_firstline");
}

infile.close();

return sLine;

}

bool ProjectSymlinkFixer::likely_an_intended_symlink(std::string filename, std::string string_to_find)
{
std::filesystem::directory_entry p(filename);
if (std::filesystem::is_symlink(p)) return true;

std::ifstream infile(filename);
bool starts_with_string = false;

if (infile.good())
{
   std::string sLine;
   getline(infile, sLine);

   if (line_count(filename) == 1)
   {
      //std::cout << sLine << std::endl;
      if (starts_with(sLine, string_to_find)) starts_with_string = true;
      if (starts_with(sLine, "../")) starts_with_string = true;
      if (starts_with(sLine, "/Users/markoates/Repos/")) starts_with_string = true;
   }
   else
   {
      // not likely a symlink, file contains more than one line
   }
}

infile.close();

return starts_with_string;

}

std::string ProjectSymlinkFixer::read_symlink(std::string filename)
{
namespace fs = std::filesystem;

std::string symlink_target;
try
{
   symlink_target = fs::read_symlink(std::filesystem::path(filename)).string();
}
catch (const std::exception& e)
{
   symlink_target = read_file_firstline(filename);
}
return symlink_target;

}

void ProjectSymlinkFixer::run()
{
namespace fs = std::filesystem;

//const std::string MAGIC_STRING = "/Users/markoates/Repos/";
const std::string MAGIC_STRING = "../../../";
std::vector<std::string> filenames = {};
//fs::directory_entry;
for(const fs::directory_entry &p : fs::recursive_directory_iterator(project_folder))
{
   std::string filename = p.path().string();
   std::replace(filename.begin(), filename.end(), '\\', '/');
   std::cout << filename << std::endl;

   if (fs::is_symlink(p) || likely_an_intended_symlink(filename, MAGIC_STRING))
   {
      std::cout << "   LIKELY" << std::endl;
      filenames.push_back(filename);
      std::string symlink_target = read_symlink(filename);
      std::string sanitized_target = symlink_target;

      std::string prefix = "";


      if (starts_with(symlink_target, MAGIC_STRING))
      {
         prefix = MAGIC_STRING;
         // this means it's a hard-coded target path
         // TODO: make this ../../../ instead count the proper number of "../" elements to prefix
         sanitized_target.replace(0, std::string(prefix).length(), "../../../");
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
         command << "ln -sf " << sanitized_target << " " << filename;
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
} // namespace Project
} // namespace Blast


