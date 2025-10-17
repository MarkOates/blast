#include <iostream>
#include <filesystem>
#include <map>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      std::cerr << "Usage: " << argv[0] << " <file_path> <destination_folder>\n";
      return 1;
   }

   fs::path original_file = argv[1];
   fs::path destination_folder = argv[2];

   if (!fs::exists(original_file))
   {
      std::cerr << "Error: File does not exist: " << original_file << "\n";
      return 1;
   }

   if (!fs::exists(destination_folder))
   {
      std::cerr << "Error: Destination folder does not exist: " << destination_folder << "\n";
      return 1;
   }

   // Define the allowed moves
   std::map<fs::path, fs::path> allowed_moves = {
      { "./tests/fixtures/bitmaps", "./bin/data/bitmaps" },
      { "./tests/fixtures/models", "./bin/data/models" },
      { "./tests/fixtures/samples", "./bin/data/samples" },
      { "./tests/fixtures/maps", "./bin/data/maps" },
      { "./tests/fixtures/animations", "./bin/data/animations" },
      { "./tests/fixtures/icons", "./bin/data/icons" },
      { "./tests/fixtures/saves", "./bin/data/saves" },
      { "./tests/fixtures/text", "./bin/data/text" }
   };

   fs::path canonical_source_dir;
   fs::path canonical_dest_dir;

   try
   {
      canonical_source_dir = fs::canonical(original_file).parent_path();
      canonical_dest_dir = fs::canonical(destination_folder);
   }
   catch (const fs::filesystem_error& e)
   {
      std::cerr << "Error resolving canonical paths: " << e.what() << "\n";
      return 1;
   }

   fs::path canonical_allowed_dest;
   bool source_found = false;

   for (const auto& move_rule : allowed_moves)
   {
      try
      {
         if (fs::canonical(move_rule.first) == canonical_source_dir)
         {
            source_found = true;
            canonical_allowed_dest = fs::canonical(move_rule.second);
            break;
         }
      }
      catch (const fs::filesystem_error& e)
      {
         // Ignore if a path in the map doesn't exist
      }
   }

   if (!source_found)
   {
      std::cerr << "Error: Moving files from \"" << canonical_source_dir.string() << "\" is not an allowed source directory.\n";
      return 1;
   }

   if (canonical_allowed_dest != canonical_dest_dir)
   {
      std::cerr << "Error: Files from \"" << canonical_source_dir.string() 
                << "\" can only be moved to \"" << canonical_allowed_dest.string()
                << "\", not \"" << canonical_dest_dir.string() << "\".\n";
      return 1;
   }

   fs::path new_file_path = destination_folder / original_file.filename();

   try
   {
      // Move the file
      fs::rename(original_file, new_file_path);

      // Create a symbolic link pointing to the new location
      fs::create_symlink(new_file_path, original_file);

      std::cout << "Moved file to: " << new_file_path << "\n";
      std::cout << "Created symlink at: " << original_file << " -> " << new_file_path << "\n";
   }
   catch (const fs::filesystem_error& e)
   {
      std::cerr << "Filesystem error: " << e.what() << "\n";
      return 1;
   }

   return 0;
}

