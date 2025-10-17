#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <set>
#include <iomanip>
#include <allegro5/allegro.h> // NOTE: This is required as part of the build and linking process

namespace fs = std::filesystem;

// Function to get the status of a single file
std::string get_status(const fs::path& path)
{
    auto status = fs::symlink_status(path); // Do not follow symlinks

    if (!fs::exists(status)) return "MISSING";
    if (fs::is_symlink(status)) return "LINKED";
    if (fs::is_regular_file(status)) return "PRESENT";
    if (fs::is_directory(status)) return "DIRECTORY";
    return "OTHER";
}

// Function to display the status UI for a category
void display_status_ui(const std::string& category, const std::map<fs::path, fs::path>& allowed_moves)
{
    fs::path source_dir;
    fs::path dest_dir;
    bool category_found = false;

    for (const auto& move_rule : allowed_moves)
    {
        if (move_rule.first.filename() == category)
        {
            source_dir = move_rule.first;
            dest_dir = move_rule.second;
            category_found = true;
            break;
        }
    }

    if (!category_found)
    {
        std::cerr << "Error: Unknown category '" << category << "'.\n";
        return;
    }

    std::cout << "Status for category: " << category << std::endl;
    std::cout << "  Fixtures source:      " << source_dir.string() << std::endl;
    std::cout << "  Production destination: " << dest_dir.string() << std::endl;
    std::cout << std::endl;

    std::set<fs::path> filenames;
    if (fs::exists(source_dir)) {
        for (const auto& entry : fs::directory_iterator(source_dir)) {
            if (fs::is_regular_file(entry) || fs::is_symlink(entry))
                filenames.insert(entry.path().filename());
        }
    }
    if (fs::exists(dest_dir)) {
        for (const auto& entry : fs::directory_iterator(dest_dir)) {
            if (fs::is_regular_file(entry))
                filenames.insert(entry.path().filename());
        }
    }

    std::cout << std::left
              << std::setw(35) << "Filename"
              << std::setw(20) << "Production"
              << std::setw(20) << "Fixtures" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto& filename : filenames)
    {
        std::string prod_status = get_status(dest_dir / filename);
        if (prod_status == "LINKED") {
            prod_status = "ERROR_IS_LINK";
        }

        std::string fix_status = get_status(source_dir / filename);

        std::cout << std::left
                  << std::setw(35) << filename.string()
                  << std::setw(20) << prod_status
                  << std::setw(20) << fix_status << std::endl;
    }
}

// Function to perform the original move and symlink operation
void move_and_symlink_file(int argc, char* argv[], const std::map<fs::path, fs::path>& allowed_moves)
{
   fs::path original_file = argv[1];
   fs::path destination_folder = argv[2];

   if (!fs::exists(original_file))
   {
      std::cerr << "Error: File does not exist: " << original_file.string() << "\n";
      return;
   }

   if (!fs::exists(destination_folder))
   {
      std::cerr << "Error: Destination folder does not exist: " << destination_folder.string() << "\n";
      return;
   }

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
      return;
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
      return;
   }

   if (canonical_allowed_dest != canonical_dest_dir)
   {
      std::cerr << "Error: Files from \"" << canonical_source_dir.string() 
                << "\" can only be moved to \"" << canonical_allowed_dest.string()
                << "\", not \"" << canonical_dest_dir.string() << "\".\n";
      return;
   }

   fs::path new_file_path = destination_folder / original_file.filename();

   try
   {
      // Move the file
      fs::rename(original_file, new_file_path);

      // Create a symbolic link pointing to the new location
      fs::create_symlink(new_file_path, original_file);

      std::cout << "Moved file to: " << new_file_path.string() << "\n";
      std::cout << "Created symlink at: " << original_file.string() << " -> " << new_file_path.string() << "\n";
   }
   catch (const fs::filesystem_error& e)
   {
      std::cerr << "Filesystem error: " << e.what() << "\n";
      return;
   }
}

int main(int argc, char* argv[])
{
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

   if (argc == 2)
   {
      display_status_ui(argv[1], allowed_moves);
   }
   else if (argc == 3)
   {
      move_and_symlink_file(argc, argv, allowed_moves);
   }
   else
   {
      std::cerr << "Usage: " << std::endl;
      std::cerr << "  To view status: " << argv[0] << " <category>" << std::endl;
      std::cerr << "    e.g. " << argv[0] << " bitmaps" << std::endl;
      std::cerr << "  To move a file: " << argv[0] << " <file_to_move> <destination_folder>" << std::endl;
      return 1;
   }

   return 0;
}

