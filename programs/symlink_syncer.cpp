// https://chatgpt.com/c/6814d0b9-8a44-800f-8253-0b13106c823f



#include <iostream>
#include <filesystem>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>
#include <allegro5/allegro.h>

namespace fs = std::filesystem;

struct FileEntry
{
   std::string name;
   fs::file_time_type last_modified;
};

std::vector<FileEntry> get_regular_files(const fs::path &directory_path)
{
   std::vector<FileEntry> files;

   if (fs::exists(directory_path) && fs::is_directory(directory_path))
   {
      for (const auto &entry : fs::directory_iterator(directory_path))
      {
         if (fs::is_regular_file(fs::status(entry)))
         {
            files.push_back({
               entry.path().filename().string(),
               fs::last_write_time(entry)
            });
         }
      }
   }

   return files;
}

int main(int argc, char **argv)
//int main()
{
   fs::path dir_a = "/Users/markoates/Repos/Atratus/bin/data/models";
   fs::path dir_b = "/Users/markoates/Repos/Atratus/tests/fixtures/models";

   std::vector<FileEntry> files_in_a = get_regular_files(dir_a);
   std::vector<FileEntry> files_in_b = get_regular_files(dir_b);

   // Create a set of filenames in B for fast lookup
   std::set<std::string> files_in_b_names;
   for (const auto &f : files_in_b)
   {
      files_in_b_names.insert(f.name);
   }

   // Filter files that are in A but not in B
   std::vector<FileEntry> unique_to_a;
   for (const auto &f : files_in_a)
   {
      if (files_in_b_names.find(f.name) == files_in_b_names.end())
      {
         unique_to_a.push_back(f);
      }
   }

   // Sort by last modified time (ascending)
   std::sort(unique_to_a.begin(), unique_to_a.end(),
             [](const FileEntry &a, const FileEntry &b)
             {
                return a.last_modified > b.last_modified;
             });

   std::cout << "Files in " << dir_a << " but not in " << dir_b << " (sorted by last modified):\n";
   for (const auto &f : unique_to_a)
   {
      std::cout << f.name << '\n';
   }



   std::cout << "==========" << std::endl;

   for (const auto &f : unique_to_a)
   {
      std::stringstream symlink_command;
      symlink_command << "(cd " << dir_b << " && ln -s " << dir_a / f.name << ")";
      std::cout << symlink_command.str() << std::endl;
   }


   return 0;
}


