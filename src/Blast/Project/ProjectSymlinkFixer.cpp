

#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <fstream>
#include <iterator>
#include <Blast/Project/SymlinkChecker.hpp>
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


std::string ProjectSymlinkFixer::get_project_folder() const
{
   return project_folder;
}


bool ProjectSymlinkFixer::starts_with(std::string source, std::string string_to_find)
{
   return source.rfind(string_to_find, 0) == 0;
}

int ProjectSymlinkFixer::has_one_line(std::string filename)
{
   std::string s;
   int sTotal = 0;

   std::ifstream in;
   in.open(filename);

   while(!in.eof()) {
     getline(in, s);
     sTotal ++;
   }

   in.close();
   return sTotal == 1;
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

   if (std::filesystem::is_directory(p)) return false;

   if (!std::filesystem::exists(p))
   {
      std::stringstream error_message;
      error_message << "File \"" << filename << "\" does not exist when running likely_an_intended_symlink.";
      throw std::runtime_error(error_message.str());
   }

   //std::filesystem::directory_entry p(filename);
   std::string absolute_filename = std::filesystem::absolute(p).string();

   if (std::filesystem::is_symlink(p) || Blast::Project::SymlinkChecker(absolute_filename).is_symlink())
   {
      return true;
      // this doesn't work for some reason
   }

   //if (Blast::Project::SymlinkChecker(filename).is_symlink()) return true; // this doesn't work for some reason

   std::ifstream infile(filename);
   bool starts_with_string = false;

   if (infile.good())
   {
      if (has_one_line(filename))
      {
         std::string sLine;
         getline(infile, sLine);

         if (starts_with(sLine, "../")) starts_with_string = true;
         if (starts_with(sLine, "/Users/markoates/Repos/")) starts_with_string = true;
      }
      else
      {
         // not likely a symlink, file contains more than one line
      }
   }
   else
   {
      std::stringstream error_message;
      error_message << "Unable to read file \"" << filename << "\" when running likely_an_intended_symlink.";
      throw std::runtime_error(error_message.str());
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

         #ifdef _WIN32
         bool do_symlink_fixing_for_win = true;
         #else
         bool do_symlink_fixing_for_win = false;
         #endif


         if (starts_with(symlink_target, MAGIC_STRING))
         {
            prefix = MAGIC_STRING;
            // this means it's a hard-coded target path
            // TODO: make this ../../../ instead count the proper number of "../" elements to prefix

            if (do_symlink_fixing_for_win)
            {
               // NOTE. This ProjectSymlinkFixer tool is used for two different purposes.  One is
               // inside a Windows environment, to fix symlinks from project trees that enter the system
               // from outside OS environments, for example, projects that are developed in a MacOS
               // environment and then cloned into a Windows environment for development and testing.
               // There tends to be an asymmetry in how symlinks are implemented across these platforms.
               // So, for the time being, this tool will use this "prefix" patch in this if branch for
               // that purpose...
               sanitized_target.replace(0, std::string(prefix).length(), "../../../");
            }
            else
            {
               //... However, in the use case in *this* conditional branch, the ProjectSymlinkFixer is used
               // by the SourceReleaseBuilder, which combs through the directory in the release folder and
               // swaps out symlinks with their real sources.  In this case, the relative path name
               // that already exists inside the symlink file will not accurately point to the target
               // because the "releaser" process (the process for the SourceReleaseBuilder) copies the
               // symlinks to a fresh destination folder to assemble the release.  In this case
               // this "ProjectSymlinkFixer" nees to replace the symlink target path in the file
               // with a full hard-coded pathname, and that's the use case for this branch
               // Note that the releaser is used so infrequently and has very specific use cases that
               // the process has not been coded to be flexible.
               sanitized_target.replace(0, std::string(prefix).length(), "/Users/markoates/Repos/");
            }
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


