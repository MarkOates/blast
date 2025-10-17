#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <set>
#include <iomanip>
#include <allegro5/allegro.h> // NOTE: This is required as part of the build and linking process

namespace fs = std::filesystem;

const std::string COLOR_LIGHT_BLUE = "\033[94m";
const std::string BG_DARK_RED = "\033[41m";
const std::string COLOR_ORANGE_YELLOW = "\033[93m";
const std::string COLOR_LAVENDER = "\033[95m";
const std::string COLOR_RESET = "\033[0m";

// Core function to perform the move and symlink
void perform_move_and_symlink(const fs::path& source_file, const fs::path& dest_folder)
{
   fs::path new_file_path = dest_folder / source_file.filename();

   try
   {
      // Move the file
      fs::rename(source_file, new_file_path);

      // Create a symbolic link pointing to the new location
      fs::create_symlink(new_file_path, source_file);

      std::cout << "Moved file to: " << new_file_path.string() << "\n";
      std::cout << "Created symlink at: " << source_file.string() << " -> " << new_file_path.string() << "\n";
   }
   catch (const fs::filesystem_error& e)
   {
      std::cerr << "Filesystem error: " << e.what() << "\n";
   }
}


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

    // Determine column widths
    size_t filename_col_width = std::string("Filename").length();
    for (const auto& filename : filenames)
    {
        if (filename.string().length() > filename_col_width)
        {
            filename_col_width = filename.string().length();
        }
    }
    filename_col_width += 3;

    const int status_col_width = 20;

    // Print table header
    std::cout << std::left
              << std::setw(filename_col_width) << "Filename"
              << std::setw(status_col_width) << "Production"
              << std::setw(status_col_width) << "Fixtures" << std::endl;
    std::cout << std::string(filename_col_width + (status_col_width * 2), '-') << std::endl;

    // Print table rows
    for (const auto& filename : filenames)
    {
        std::string prod_status_str = get_status(dest_dir / filename);
        std::string fix_status_str = get_status(source_dir / filename);

        bool is_error = (prod_status_str == "LINKED");
        bool is_synced = (prod_status_str == "PRESENT" && fix_status_str == "LINKED");
        bool needs_linking = (prod_status_str == "PRESENT" && fix_status_str == "PRESENT");
        bool needs_moving = (prod_status_str == "MISSING" && fix_status_str == "PRESENT");

        if (is_error) {
            std::cout << BG_DARK_RED;
        } else if (is_synced) {
            std::cout << COLOR_LIGHT_BLUE;
        } else if (needs_linking) {
            std::cout << COLOR_LAVENDER;
        } else if (needs_moving) {
            std::cout << COLOR_ORANGE_YELLOW;
        }

        std::string display_prod_status = is_error ? "ERROR_IS_LINK" : prod_status_str;

        std::cout << std::left
                  << std::setw(filename_col_width) << filename.string()
                  << std::setw(status_col_width) << display_prod_status
                  << std::setw(status_col_width) << fix_status_str
                  << COLOR_RESET << std::endl;
    }
}

// Function for the original manual move and symlink operation
void manual_move_and_symlink_file(int argc, char* argv[], const std::map<fs::path, fs::path>& allowed_moves)
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

   perform_move_and_symlink(original_file, destination_folder);
}

// Function for the new automatic symlinking by filename
void auto_symlink_by_filename(const std::string& filename, const std::map<fs::path, fs::path>& allowed_moves)
{
    fs::path source_file_path;
    fs::path dest_folder_path;
    bool file_found_in_fixtures = false;

    // Search for the file in all allowed fixture directories
    for (const auto& move_rule : allowed_moves)
    {
        fs::path potential_path = move_rule.first / filename;
        if (fs::exists(potential_path) && fs::is_regular_file(potential_path))
        {
            source_file_path = potential_path;
            dest_folder_path = move_rule.second;
            file_found_in_fixtures = true;
            break;
        }
    }

    if (!file_found_in_fixtures)
    {
        std::cerr << "Error: File '" << filename << "' not found in any of the configured fixture directories." << std::endl;
        return;
    }

    // Check statuses
    std::string fix_status = get_status(source_file_path);
    std::string prod_status = get_status(dest_folder_path / filename);

    // Conditionally perform the action
    if (fix_status == "PRESENT" && prod_status == "MISSING")
    {
        std::cout << "File '" << filename << "' is present in fixtures and missing in production. Performing move..." << std::endl;
        perform_move_and_symlink(source_file_path, dest_folder_path);
    }
    else
    {
        std::cout << "File '" << filename << "' does not meet the criteria for automatic symlinking." << std::endl;
        std::cout << "  Production status: " << prod_status << std::endl;
        std::cout << "  Fixtures status:   " << fix_status << std::endl;
        std::cout << "No action taken." << std::endl;
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
      std::string arg = argv[1];
      bool is_category = false;
      for (const auto& move_rule : allowed_moves)
      {
         if (move_rule.first.filename() == arg)
         {
            is_category = true;
            break;
         }
      }

      if (is_category)
      {
         display_status_ui(arg, allowed_moves);
      }
      else
      {
         auto_symlink_by_filename(arg, allowed_moves);
      }
   }
   else if (argc == 3)
   {
      manual_move_and_symlink_file(argc, argv, allowed_moves);
   }
   else
   {
      std::cerr << "Usage: " << std::endl;
      std::cerr << "  To view status: " << argv[0] << " <category>" << std::endl;
      std::cerr << "    e.g. " << argv[0] << " bitmaps" << std::endl;
      std::cerr << "  To move a file manually: " << argv[0] << " <file_to_move> <destination_folder>" << std::endl;
      std::cerr << "  To auto-symlink a file: " << argv[0] << " <filename>" << std::endl;
      std::cerr << "    e.g. " << argv[0] << " my_cool_image.png" << std::endl;
      return 1;
   }

   return 0;
}

