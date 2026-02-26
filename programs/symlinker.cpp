#include <iostream>
#include <filesystem>
#include <map>
#include <string>
#include <set>
#include <iomanip>
#include <sstream>
#include <allegro5/allegro.h> // NOTE: This is required as part of the build and linking process

namespace fs = std::filesystem;

const std::string COLOR_LIGHT_BLUE = "\033[94m";
const std::string BG_DARK_RED = "\033[41m";
const std::string COLOR_ORANGE_YELLOW = "\033[93m";
const std::string COLOR_LAVENDER = "\033[95m";
const std::string COLOR_RESET = "\033[0m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_LIGHT_GREEN = "\033[92m";
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_LIGHT_RED = "\033[91m";


enum class FileStatus
{
   FILE_STATUS_UNDEF,
   FILE_STATUS_MISSING,
   FILE_STATUS_LINKED,
   FILE_STATUS_PRESENT,
   FILE_STATUS_DIRECTORY,
   FILE_STATUS_OTHER,
};


std::string to_string(FileStatus file_status)
{
   switch(file_status)
   {
      case FileStatus::FILE_STATUS_MISSING: return "MISSING";
      case FileStatus::FILE_STATUS_LINKED: return "LINKED";
      case FileStatus::FILE_STATUS_PRESENT: return "PRESENT";
      case FileStatus::FILE_STATUS_DIRECTORY: return "DIRECTORY";
      case FileStatus::FILE_STATUS_OTHER: return "OTHER";
      default: throw std::runtime_error("file_status_to_string: Uhandled type " + std::to_string((int)file_status));
   }
}


void throw_error(std::string error_message)
{
   std::stringstream ss;
   ss << COLOR_RED << error_message << COLOR_RESET;
   std::cerr << ss.str() << std::endl;
   throw std::runtime_error(ss.str());
}


void output_happy_error(std::string error_message)
{
   std::stringstream ss;
   ss << COLOR_LIGHT_GREEN << error_message << COLOR_RESET;
   std::cerr << ss.str() << std::endl;
   throw std::runtime_error(ss.str());
}



bool is_linked_or_present(FileStatus file_status)
{
   return file_status == FileStatus::FILE_STATUS_LINKED || file_status == FileStatus::FILE_STATUS_PRESENT;
}


bool is_present_as_file(FileStatus file_status)
{
   return file_status == FileStatus::FILE_STATUS_PRESENT;
}


bool is_missing(FileStatus file_status)
{
   return file_status == FileStatus::FILE_STATUS_MISSING;
}



bool validate_symlink( // by ChatGPT
   const fs::path& symlink_file_and_path,
   const fs::path& expected_relative_target)
{
   std::error_code ec;

   // 1. Does the path exist (even if dangling)?
   if (!fs::exists(fs::symlink_status(symlink_file_and_path, ec)))
   {
      return false;
   }

   // 2. Is it actually a symlink?
   if (!fs::is_symlink(fs::symlink_status(symlink_file_and_path, ec)))
   {
      return false;
   }

   // 3. Read the symlink target (exact value stored in the link)
   fs::path actual_target = fs::read_symlink(symlink_file_and_path, ec);
   if (ec)
   {
      return false;
   }

   // 4. Compare the raw target value (relative path preserved)
   return actual_target == expected_relative_target;
}




// Core function to perform the move and symlink
void perform_move_and_symlink(const fs::path& source_file, const fs::path& dest_folder)
{
   throw_error("Unfortunately, this feature does not work and was not implemented correctly by the AI.");
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


FileStatus get_status(const fs::path& path)
{
   auto status = fs::symlink_status(path); // Do not follow symlinks

   if (!fs::exists(status)) return FileStatus::FILE_STATUS_MISSING;
   if (fs::is_symlink(status)) return FileStatus::FILE_STATUS_LINKED;
   if (fs::is_regular_file(status)) return FileStatus::FILE_STATUS_PRESENT;
   if (fs::is_directory(status)) return FileStatus::FILE_STATUS_DIRECTORY;
   return FileStatus::FILE_STATUS_OTHER;
}


std::string get_status_str(const fs::path& path)
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
        std::string prod_status_str = get_status_str(dest_dir / filename);
        std::string fix_status_str = get_status_str(source_dir / filename);

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
   std::vector<std::pair<std::pair<fs::path, FileStatus>, std::pair<fs::path, FileStatus>>> found_paths;

   for (auto &allowed_move : allowed_moves)
   {
      const fs::path &production_directory = allowed_move.second;
      const fs::path &fixtures_directory = allowed_move.first;
      auto status_in_production_folder = get_status(production_directory / filename);
      auto status_in_fixtures_folder = get_status(fixtures_directory / filename);

      //std::cout << "--- " << production_directory / filename << std::endl;
      //std::cout << "    " << to_string(status_in_production_folder) << std::endl;
      //std::cout << "  - " << fixtures_directory / filename << std::endl;
      //std::cout << "    " << to_string(status_in_fixtures_folder) << std::endl;

      if (is_linked_or_present(status_in_production_folder) || is_linked_or_present(status_in_fixtures_folder))
      {
         found_paths.push_back({
            { production_directory, status_in_production_folder },
            { fixtures_directory, status_in_fixtures_folder },
         });
      }
   }

   if (found_paths.empty())
   {
      std::cerr << "Error: File '" << filename << "' not found in any of the configured fixture directories." << std::endl;
      return;
   }
   if (found_paths.size() >= 2)
   {
      std::cerr << "Error: The file '" << filename << "' was found in more than one of the possible directory categories." << std::endl;
      return;
   }

   //for (auto &found_path : found_paths)
   //{
      //std::cout << "The following paths are candidates:" << std::endl;
      //std::cout << "  - " << found_path.first.first << std::endl;
      //std::cout << "    " << found_path.second.first << std::endl;
   //}

   auto &found_path = found_paths[0];
   const fs::path &production_directory = found_path.first.first;
   const fs::path &fixtures_directory = found_path.second.first;
   auto status_in_production_folder = found_path.first.second;
   auto status_in_fixtures_folder = found_path.second.second; 
   auto production_directory_and_file = found_path.first.first / filename;
   auto fixtures_directory_and_file = found_path.second.first / filename;


   bool is_error = (status_in_production_folder == FileStatus::FILE_STATUS_LINKED);
   bool is_synced = (status_in_production_folder == FileStatus::FILE_STATUS_PRESENT)
                  && (status_in_fixtures_folder == FileStatus::FILE_STATUS_LINKED);
   bool copies_in_both = (status_in_production_folder == FileStatus::FILE_STATUS_PRESENT)
                      && (status_in_fixtures_folder == FileStatus::FILE_STATUS_PRESENT);
   bool needs_reloation = (status_in_production_folder == FileStatus::FILE_STATUS_MISSING)
                        && (status_in_fixtures_folder == FileStatus::FILE_STATUS_PRESENT);
   bool needs_symlink_in_fixtures = (status_in_production_folder == FileStatus::FILE_STATUS_PRESENT)
                                && (status_in_fixtures_folder == FileStatus::FILE_STATUS_MISSING);

   if (is_error)
   {
      throw_error("Cannot operate: SYMLINK_IN_PRODUCTION: The file is in production as a symlink.");
   }
   if (is_synced)
   {
      output_happy_error("Cannot operate: IS_SYNCED: The files already exists as a file in production and symlinked in fixtures.");
      return;
   }
   if (copies_in_both)
   {
      throw_error(
            "Cannot operate: COPIES_IN_BOTH: A file exists in production and another in fixtures."
            "\n - " + std::string(fixtures_directory_and_file) +
            "\n - " + std::string(production_directory_and_file)
         );
      return;
   }
   if (needs_reloation)
   {
      throw_error("Cannot operate: FILE_ONLY_IN_FIXTURES: The file exists in fixtures and needs to be moved into production. This action is not yet implemented (you can do it if you want :) )");
      return;
   }
   if (needs_symlink_in_fixtures)
   {
      //throw_error("Cannot operate: FILE_ONLY_IN_FIXTURES: The file exists in fixtures and needs to be moved into production.");
      std::string symlink_target_as_relative_path = std::filesystem::path("../../../") / production_directory_and_file;
      std::string symlink_file_and_path = fixtures_directory_and_file;

      std::cout << COLOR_LIGHT_GREEN
                << "File was successfully located in the production fixtures folder at "
                << "\"" + production_directory_and_file.string() + "\""
                << " and, as expected, no correlated file or symlink is present in the fixtures folder."
                << COLOR_RESET;

      std::cout << std::endl;

      std::cout << COLOR_LAVENDER 
                << "Creating a symlink with the following values:" << std::endl
                << "    - original file at: \"" + production_directory_and_file.string() + "\"" << std::endl
                << "       symlink file at: \"" + symlink_file_and_path + "\"" << std::endl
                << "        symlink target: \"" + symlink_target_as_relative_path + "\"" << std::endl
                << COLOR_RESET;

      fs::create_symlink(symlink_target_as_relative_path, symlink_file_and_path);

      bool symlink_is_validated = validate_symlink(symlink_file_and_path, symlink_target_as_relative_path);

      if (!symlink_is_validated)
      {
         throw_error("ERROR: Symlink file was created but there was an error in the symlink when validating it's correctness.");
      }

      std::cout << COLOR_LIGHT_GREEN 
                << " -*-*~*#*# # # # # # # # # # # # # # # # # # # # # # # # # #*#*~*-*- " << std::endl
                << " -*-*~*#*# Symlink was created and validated SUCCESSFULLY #*#*~*-*- " << std::endl
                << " -*-*~*#*# # # # # # # # # # # # # # # # # # # # # # # # # #*#*~*-*- " << std::endl
                << COLOR_RESET;


      return;
   }


   //bool is_error = (prod_status_str == "LINKED");
   //bool is_synced = (prod_status_str == "PRESENT" && fix_status_str == "LINKED");
   //bool needs_linking = (prod_status_str == "PRESENT" && fix_status_str == "PRESENT");
   //bool needs_moving = (prod_status_str == "MISSING" && fix_status_str == "PRESENT");

   throw_error("auto_symlink_by_filename: ERROR: Handling the file states in their current condition has not been implemented.");



    //fs::path source_file_path;
    //fs::path dest_folder_path;
    //bool file_found_in_fixtures = false;

    //// Search for the file in all allowed fixture directories
    //for (const auto& move_rule : allowed_moves)
    //{
        //fs::path potential_path = move_rule.first / filename;
        //if (fs::exists(potential_path) && fs::is_regular_file(potential_path))
        //{
            //source_file_path = potential_path;
            //dest_folder_path = move_rule.second;
            //file_found_in_fixtures = true;
            //break;
        //}
    //}



    //if (!file_found_in_fixtures)
    //{
        //std::cerr << "Error: File '" << filename << "' not found in any of the configured fixture directories." << std::endl;
        //return;
    //}

    //// Check statuses
    //std::string fix_status = get_status(source_file_path);
    //std::string prod_status = get_status(dest_folder_path / filename);

    //// Conditionally perform the action
    //if (fix_status == "PRESENT" && prod_status == "MISSING")
    //{
        //std::cout << "File '" << filename << "' is present in fixtures and missing in production. Performing move..." << std::endl;
        //perform_move_and_symlink(source_file_path, dest_folder_path);
    //}
    //else
    //{
        //std::cout << "File '" << filename << "' does not meet the criteria for automatic symlinking." << std::endl;
        //std::cout << "  Production status: " << prod_status << std::endl;
        //std::cout << "  Fixtures status:   " << fix_status << std::endl;
        //std::cout << "No action taken." << std::endl;
    //}
}


int main(int argc, char* argv[])
{
   al_init();

   //ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   //al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
   //al_destroy_path(resource_path);

   std::cout << "Working in path: \"" << std::filesystem::current_path() << "\"" << std::endl;

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

   al_uninstall_system();

   return 0;
}


