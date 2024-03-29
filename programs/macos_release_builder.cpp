



// !!!!!!
// Please read this document which outlines the steps involved:
// https://docs.google.com/document/d/1nTsH72zSUxwj--fjOwiCnbI7XXGvQvUtuvOSf5f5KVs/edit#


#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_YELLOW "\033[1;33m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_DEFAULT "\033[0m"
#define CONSOLE_COLOR_CYAN "\033[1;36m"


#include <allegro5/allegro.h> // for compatibility with union/Makefile
#include <Blast/BuildSystem/BuildFactory.hpp>
#include <Blast/BuildSystem/ReportRenderer.hpp>
#include <iostream>
#include <sstream>
#include <Blast/SystemInfo.hpp>
#include <Blast/BuildInfo.hpp>
#include <Blast/BuildInfoBuilder.hpp>
#include <Blast/BuildInfoCppFileGenerator.hpp>
#include <Blast/Project/SourceReleaseAppInfoFile.hpp>



#define PROJECT_DIRECTORY "/Users/markoates/Repos/TestProjectDeleteMe"
#define BUILD_NUMBER "54321"


#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <Blast/String/Trimmer.hpp>
//#include <allegro_flare/useful_php.h>
#include <string>


#include <Blast/RegexMatcher.hpp>


#include <Blast/StringJoiner.hpp>



#include <fstream>
std::string file_get_contents(std::string filename)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file) return "";
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}





#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>


//std::string get_formatted_timestamp(std::chrono::system_clock::time_point time_point)
//{
  //// Get the current time in UTC
  //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  //std::time_t now_c = std::chrono::system_clock::to_time_t(now);

  //// Create a tm struct from the time_t value
  //std::tm tm = *std::gmtime(&now_c);

  //// Get the UTC offset in seconds
  //std::chrono::seconds offset = std::chrono::system_clock::now().time_since_epoch() -
                                 //std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())s;

  //// Convert the UTC offset to hours and minutes
  //int offset_hours = std::chrono::duration_cast<std::chrono::hours>(offset).count();
  //int offset_minutes = std::chrono::duration_cast<std::chrono::minutes>(offset % std::chrono::hours(1)).count();

  //// Create a stringstream to hold the formatted string
  //std::stringstream ss;

  //// Format the timestamp as "Month day year, hour:minute AM/PM Timezone Abbreviation (UTC±offset)"
  //ss << std::put_time(&tm, "%B %d %Y, %I:%M %p %Z") << " (UTC" 
     //<< (offset_hours >= 0 ? "+" : "") << offset_hours 
     //<< ":" << std::setw(2) << std::setfill('0') << std::abs(offset_minutes) << ")";

  //// Return the formatted string
  //return ss.str();
//}


std::string get_formatted_timestamp(std::chrono::system_clock::time_point time_point)
{
  // Get the current time in UTC
  std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);

  // Create a tm struct from the time_t value
  std::tm tm = *std::gmtime(&now_c);

  // Create a stringstream to hold the formatted string
  std::stringstream ss;

  // Format the timestamp as "Month day year, hour:minute AM/PM UTC"
  // TODO: Include the local time zone in which the program was built
  ss << std::put_time(&tm, "%B %d %Y, %I:%M %p UTC");

  // Return the formatted string
  return ss.str();
}





std::string trim(std::string str)
{
   return Blast::String::Trimmer(str).trim();
}


std::string TEMP_DIRECTORY_FOR_BUILD = "";
std::string TEMP_DIRECTORY_FOR_ICON = "";
std::string TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD = "";



class NameGenerator
{
public:
   static std::string SYSTEM_RELEASES_FOLDER; // "/Users/markoates/Releases/"
   static std::string SOURCE_RELEASE_FOLDER_NAME; // "TheWeepingHouse-SourceRelease-220903200818UTC"
   static std::string NAME_OF_PROJECT; // "TheWeepingHouse"
   static std::string NAME_OF_EXECUTABLE; // "TheWeepingHouse"
   static std::string COPYRIGHT_FULL_TEXT; // "Copyright 2022 - Mark Oates - www.CLUBCATT.com"
   static std::string FULL_VERSION_NUMBER_WITH_BUILD; // "1.0.0.3"
   static std::string VERSION_NUMBER; // "1.0.0"
   static std::string FULL_PATH_TO_SOURCE_ICON_PNG; // "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/data/system/allegro-flare-generic-icon-1024.png"
   static std::string CHIP_NAME; // "x86", "intel"
   static std::chrono::system_clock::time_point START_TIME_OF_BUILD;


   //static std::string FULL_URL_OF_FILE_TO_DOWNLOAD;



   static std::string TEMP_DIRECTORY_FOR_BUILD; // is generated
   static std::string TEMP_DIRECTORY_FOR_ICON;  // is generated
   static std::string TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD;  // is generated


   static std::string source_release_folder_name() { return NameGenerator::SOURCE_RELEASE_FOLDER_NAME; }
   static std::string name_of_executable() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string readme_filename() { return "README.md"; }
   static std::string source_icon_filename() { return "Icon1024.png"; }
   static std::string built_icns_filename() { return "MyIcon.icns"; }
   static std::string app_info_filename() { return Blast::Project::SourceReleaseAppInfoFile::APP_INFO_FILENAME; } // Right now, "app.info", might change later
   static std::string full_path_of_temp_location() { return NameGenerator::TEMP_DIRECTORY_FOR_BUILD + "/"; }
   //static std::string full_path_of_source_icon_file() { return NameGenerator::TEMP_DIRECTORY_FOR_BUILD + "/"; }
   static std::string full_path_to_built_icns_file() { return NameGenerator::TEMP_DIRECTORY_FOR_ICON + "/" + built_icns_filename(); };
   static std::string name_of_project() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string name_of_built_executable() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string app_package_executable_name() { return NameGenerator::NAME_OF_EXECUTABLE; }
   static std::string app_package_folder_name() { return NameGenerator::NAME_OF_EXECUTABLE + ".app"; }
   static std::string full_path_to_copied_source_icns_file() { return NameGenerator::TEMP_DIRECTORY_FOR_ICON + "/" + source_icon_filename(); }
   static std::string release_folder_relative_to_system_releases_folder() { return NameGenerator::NAME_OF_EXECUTABLE + "-" + NameGenerator::VERSION_NUMBER + "-macos-" + NameGenerator::CHIP_NAME; }
   static std::string full_path_to_result_info_dot_plist_file()
   {
      return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/" + NAME_OF_EXECUTABLE + ".app/Contents/Info.plist";
      // concretion:
      //return SYSTEM_RELEASES_FOLDER + "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Info.plist";
   }

   static std::string release_zip_filename() { return release_folder_relative_to_system_releases_folder() + ".zip"; }
   // TODO: remove these intermediate "/" additions, validate "/" is appended when assigned
   static std::string full_path_of_source_release_folder() { return SYSTEM_RELEASES_FOLDER + "/" + NameGenerator::SOURCE_RELEASE_FOLDER_NAME; }
   static std::string full_path_to_destination_icns_file()
   {
      return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/" + NameGenerator::NAME_OF_EXECUTABLE + ".app/Contents/Resources/Icon.icns";
      // concretion:
      //return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/TheWeepingHouse.app/Contents/Resources/Icon.icns";
   }
   static std::string full_path_to_source_readme() { return (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::readme_filename()); }
   static std::string full_path_to_source_app_info_file() { return (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::app_info_filename()); }
   static std::string full_path_of_source_data_folder() { return (TEMP_DIRECTORY_FOR_BUILD + "/data/"); }
   static std::string full_path_to_destination_readme() { return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/" + "README.md"; }
   static std::string full_path_of_destination_data_folder()
   {
      return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/" + NameGenerator::NAME_OF_EXECUTABLE + ".app/Contents/Resources/data";
      // concretion:
      //return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/TheWeepingHouse.app/Contents/Resources/data";
   }
   static std::string release_folder_location() { return SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder(); }
   static std::string full_binary_app_package_destination()
   {
      return (SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/" + NameGenerator::NAME_OF_EXECUTABLE + ".app/Contents/MacOS/" + NameGenerator::name_of_built_executable());
      // concretion:
      //return (SYSTEM_RELEASES_FOLDER + "/" + release_folder_relative_to_system_releases_folder() + "/TheWeepingHouse.app/Contents/MacOS/" + NameGenerator::name_of_built_executable());
   }
   static std::string full_path_to_temp_directory_for_zip_download()
   {
      return TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD + "/";
   }
   static std::string full_path_to_local_destination_of_downloaded_zip_file()
   {
      return TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD + "/" + SOURCE_RELEASE_FOLDER_NAME + ".zip";
   }
   static std::string full_path_to_local_destination_of_unzipped_downloaded_zip_file_folder()
   {
      return TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD + "/" + SOURCE_RELEASE_FOLDER_NAME;
   }
   static std::string full_url_of_file_to_download()
   {
      //return TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD + "/" + SOURCE_RELEASE_FOLDER_NAME + ".zip";
      return "https://storage.googleapis.com/clubcatt-games-bucket/" + SOURCE_RELEASE_FOLDER_NAME + ".zip";
   }
   static std::string get_time_of_build_string()
   {
      return get_formatted_timestamp(START_TIME_OF_BUILD);
   }


   // some example concretions:
   //static std::string release_folder_relative_to_system_releases_folder() { return "TheWeepingHouse-MacOS-chip_unknown"; }
   //static std::string release_zip_filename() { return "TheWeepingHouse-MacOS-chip_unknown.zip"; }
   //static std::string full_path_of_source_release_folder() { return "/Users/markoates/Releases/" + NameGenerator::SOURCE_RELEASE_FOLDER_NAME; }
   //static std::string full_path_to_destination_icns_file() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/Icon.icns"; }
   //static std::string full_path_to_source_readme() { return (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::readme_filename()); }
   //static std::string full_path_of_source_data_folder() { return (TEMP_DIRECTORY_FOR_BUILD + "/data/"); }
   //static std::string full_path_to_destination_readme() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/README.md"; }
   //static std::string full_path_of_destination_data_folder() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/data"; }
   //static std::string release_folder_location() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown"; }
   //static std::string full_binary_app_package_destination() { return ("/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS/" + NameGenerator::name_of_built_executable()); }
};


std::string NameGenerator::SYSTEM_RELEASES_FOLDER; // "/Users/markoates/Releases/"
std::string NameGenerator::SOURCE_RELEASE_FOLDER_NAME; // "TheWeepingHouse-SourceRelease-220903200818UTC"
std::string NameGenerator::NAME_OF_EXECUTABLE; // "TheWeepingHouse"
std::string NameGenerator::COPYRIGHT_FULL_TEXT; // "Copyright 2022 - Mark Oates - www.CLUBCATT.com"
std::string NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD; // "1.0.0.3"
std::string NameGenerator::VERSION_NUMBER; // "1.0.0"
std::string NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG; // "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/data/system/allegro-flare-generic-icon-1024.png"
std::string NameGenerator::TEMP_DIRECTORY_FOR_BUILD; // auto-generated, different each run
std::string NameGenerator::TEMP_DIRECTORY_FOR_ICON; // auto-generated, different each run
std::string NameGenerator::TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD; // auto-generated, different each run
std::string NameGenerator::CHIP_NAME; // "x86", "intel", "arm", currently is "unknown-chip", tho
std::chrono::system_clock::time_point NameGenerator::START_TIME_OF_BUILD; // will be std::chrono::system_clock::now(), set at the start of build



//std::string NameGenerator::FULL_URL_OF_FILE_TO_DOWNLOAD;



//#define SOURCE_RELEASE_FOLDER_NAME NameGenerator::SOURCE_RELEASE_FOLDER_NAME
//#define NAME_OF_EXECUTABLE NameGenerator::name_of_executable()
//#define COPYRIGHT_FULL_TEXT NameGenerator::COPYRIGHT_FULL_TEXT
//#define FULL_VERSION_NUMBER_WITH_BUILD NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD
//#define VERSION_NUMBER NameGenerator::VERSION_NUMBER
//#define FULL_PATH_TO_SOURCE_ICON_PNG NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG
//#define SYSTEM_RELEASES_FOLDER NameGenerator::SYSTEM_RELEASES_FOLDER
//#define README_FILENAME NameGenerator::readme_filename()
//#define SOURCE_ICON_FILENAME NameGenerator::source_icon_filename()
//#define BUILT_ICNS_FILENAME NameGenerator::built_icns_filename()
//#define NAME_OF_GENERATED_ICNS_FILE NameGenerator::built_icns_filename()
//#define FULL_PATH_OF_TEMP_LOCATION NameGenerator::full_path_of_temp_location()
//#define FULL_PATH_OF_TEMP_LOCATION_TO_RUN_MAKE NameGenerator::full_path_of_temp_location_to_run_make()
//#define FULL_PATH_TO_BUILT_ICNS_FILE NameGenerator::full_path_to_built_icns_file()
//#define NAME_OF_BUILT_EXECUTABLE NameGenerator::name_of_built_executable()
//#define APP_PACKAGE_EXECUTABLE_NAME NameGenerator::app_package_executable_name()
//#define APP_PACKAGE_FOLDER_NAME NameGenerator::app_package_folder_name()



//static std::string full_path_to_destination_icns_file() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/Icon.icns"; }
//static std::string full_path_to_source_readme() { return (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::readme_filename()); }
//static std::string full_path_of_source_data_folder() { return (TEMP_DIRECTORY_FOR_BUILD + "/data/"); }
//static std::string full_path_to_destination_readme() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/README.md"; }
//static std::string full_path_of_destination_data_folder() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/data"; }
//static std::string release_folder_location() { return "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown"; }
//static std::string full_binary_app_package_destination() { return ("/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS/" + NameGenerator::name_of_built_executable()); }



//#define FULL_PATH_TO_DESTINATION_ICNS_FILE "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/Icon.icns"
//#define FULL_PATH_TO_SOURCE_README (TEMP_DIRECTORY_FOR_BUILD + "/" + NameGenerator::readme_filename())
//#define FULL_PATH_OF_SOURCE_DATA_FOLDER (TEMP_DIRECTORY_FOR_BUILD + "/data/")
//#define FULL_PATH_TO_DESTINATION_README "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/README.md"
//#define FULL_PATH_OF_DESTINATION_DATA_FOLDER "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources/data"
//#define RELEASE_FOLDER_LOCATION "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown"
//#define FULL_BINARY_APP_PACKAGE_DESTINATION ("/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS/" + NameGenerator::name_of_built_executable())

//#define FULL_PATH_TO_COPIED_SOURCE_ICNS_FILE NameGenerator::full_path_to_copied_source_icns_file()
//#define FULL_PATH_OF_SOURCE_RELEASE_FOLDER "/Users/markoates/Releases/TheWeepingHouse-SourceRelease-220903200818UTC/"
//#define FULL_PATH_TO_RELEASE_ZIP_FILE "/Users/markoates/Releases/TheWeepingHouse-MacOS-chip_unknown.zip"
//#define RELEASE_ZIP_FILENAME "TheWeepingHouse-MacOS-chip_unknown.zip"
//#define RELEASE_FOLDER_RELATIVE_TO_SYSTEM_RELEASES_FOLDER "TheWeepingHouse-MacOS-chip_unknown"



#include <fstream>
bool file_put_contents(std::string filename, std::string contents)
{
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << contents.c_str();
   file.close();
   return true;
}





class ExpressionMatcher
{
public:
   std::string expression;
   std::string actual;

public:
   ExpressionMatcher(std::string expression=".*", std::string actual="foo")
      : expression(expression)
      , actual(actual)
   {}

   bool matches()
   {
      return !Blast::RegexMatcher(actual, expression).get_match_info().empty();
   }
};





class ValidateIconutil : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "iconutil";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateIconutil";

   ValidateIconutil()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "Usage: iconutil --convert "; //\( icns | iconset\) ";//\[\-\-output file\] file \[icon\-name\]";
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class ValidateDylibBundlerVersion : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "dylibbundler";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateDylibBundlerVersion";

   ValidateDylibBundlerVersion()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "dylibbundler is a utility that helps bundle dynamic libraries inside macOS app bundles.\n";
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class ValidateXattrVersion : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_dylibbuilder_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "xattr -h";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateXattrVersion";

   ValidateXattrVersion()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "\nThe first form lists the names of all xattrs on the given"; // a line from the help file
      std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};





#include <stdlib.h>
std::string build_temp_filename()
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
   std::string temp_filename = std::tmpnam(nullptr);
#pragma clang diagnostic pop
   return temp_filename;
}



class ValidateSips : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string cout_temp_file;
   std::string execute_shell_command()
   {
      cout_temp_file = build_temp_filename();
      //std::cout << "filename: " << filename << std::endl;
      //throw std::runtime_error("foo");

      std::stringstream shell_command;
      shell_command << "sips -v > " << cout_temp_file;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }
   std::string temp_file_contents()
   {
      return file_get_contents(cout_temp_file);
   }

public:
   static constexpr char* TYPE = (char*)"ValidateSips";

   ValidateSips()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "sips-[0-9]+\n";
      execute_shell_command();
      std::string actual_string = temp_file_contents();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};


class ValidateZip : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "zip -v";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateZip";

   ValidateZip()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "Copyright \\(c\\) 1990-2008 Info-ZIP - Type ";
      std::string actual_string = get_result_of_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class ValidateUnzip : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "unzip -v";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateUnzip";

   ValidateUnzip()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "^UnZip [0-9]+.[0-9]+ of [0-9]+ ";
      std::string actual_string = get_result_of_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class ValidateCurl : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << "curl --version";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidateCurl";

   ValidateCurl()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      std::string match_expression = "^curl [0-9]+.[0-9]+.[0-9]+ ";
      std::string actual_string = get_result_of_shell_execution();
      if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};



class VerifySourceReleaseZipFileIsAvailableForDownloading : public Blast::BuildSystem::BuildStages::Base
{
private:
   //curl -s -o /dev/null -w "%{http_code}" "https://storage.googleapis.com/clubcatt-games-bucket/FadeToWhite-0.0.1-SourceRelease.zip"

   void execute_shell_commands()
   {
      //"https://storage.googleapis.com/clubcatt-games-bucket/FadeToWhite-0.0.1-SourceRelease.zip"
      std::stringstream shell_command;
      shell_command << "curl -s -o /dev/null -w \"%{http_code}\" \"" << full_url_of_file_to_download << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"VerifySourceReleaseZipFileIsAvailableForDownloading";
   std::string full_path_to_local_destination_of_downloaded_zip_file;
   std::string full_url_of_file_to_download;
   std::string shell_command_result;
   std::string shell_command_response_code;

   VerifySourceReleaseZipFileIsAvailableForDownloading()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_local_destination_of_downloaded_zip_file(NameGenerator::full_path_to_local_destination_of_downloaded_zip_file())
      , full_url_of_file_to_download(NameGenerator::full_url_of_file_to_download())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result != "200")
      {
         throw std::runtime_error("Shell command result is \"" + shell_command_result + "\", expecting it to be \"200\"");
         return false;
      }
      if (shell_command_response_code != "0\n")
      {
         throw std::runtime_error("Shell command response code is \"" + shell_command_response_code + "\", expecting it to be \"0\\n\"");
         return false;
      }
      return true;
   }
};



class DownloadSourceReleaseFileForBuilding : public Blast::BuildSystem::BuildStages::Base
{
private:
   // TODO: Validate presence of ZIP file, see:
   //  - https://stackoverflow.com/questions/12199059/how-to-check-if-an-url-exists-with-the-shell-and-probably-curl
   //  - https://matthewsetter.com/check-if-file-is-available-with-curl/
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "curl -L -o \"" << full_path_to_local_destination_of_downloaded_zip_file << "\" \"" << full_url_of_file_to_download << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"DownloadSourceReleaseFileForBuilding";
   std::string full_path_to_local_destination_of_downloaded_zip_file;
   std::string full_url_of_file_to_download;
   std::string shell_command_result;
   std::string shell_command_response_code;

   DownloadSourceReleaseFileForBuilding()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_local_destination_of_downloaded_zip_file(NameGenerator::full_path_to_local_destination_of_downloaded_zip_file())
      , full_url_of_file_to_download(NameGenerator::full_url_of_file_to_download())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};





class UnzipDownloadedSourceReleaseFile : public Blast::BuildSystem::BuildStages::Base
{
private:
   // TODO: Validate presence of ZIP file, see:
   //  - https://stackoverflow.com/questions/12199059/how-to-check-if-an-url-exists-with-the-shell-and-probably-curl
   //  - https://matthewsetter.com/check-if-file-is-available-with-curl/
   // TODO: Validate zip file name is shell safe
   void execute_shell_commands()
   {
      std::stringstream shell_command;

      shell_command << "unzip \"" << full_path_to_local_destination_of_downloaded_zip_file << "\" -d \"" <<  full_path_to_local_destination_for_downloading_zip_file << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"UnzipDownloadedSourceReleaseFile ";
   std::string full_path_to_local_destination_of_downloaded_zip_file;
   std::string full_path_to_local_destination_for_downloading_zip_file;
   std::string shell_command_result;
   std::string shell_command_response_code;

   UnzipDownloadedSourceReleaseFile ()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_local_destination_of_downloaded_zip_file(NameGenerator::full_path_to_local_destination_of_downloaded_zip_file())
      , full_path_to_local_destination_for_downloading_zip_file(NameGenerator::full_path_to_temp_directory_for_zip_download())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};


   //static std::string full_path_to_local_destination_of_unzipped_downloaded_zip_file_folder()




class CopyUnzippedSourceReleaseFilesToTemporaryDirectoryForBuild : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end of "name_of_unzipped_source_release_files_folder"
      std::stringstream shell_command;
      shell_command << "cp -R \"" << name_of_unzipped_source_release_files_folder << "\"/* \"" << name_of_temp_location_to_build << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyUnzippedSourceReleaseFilesToTemporaryDirectoryForBuild";
   std::string name_of_unzipped_source_release_files_folder;
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyUnzippedSourceReleaseFilesToTemporaryDirectoryForBuild()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_unzipped_source_release_files_folder(NameGenerator::full_path_to_local_destination_of_unzipped_downloaded_zip_file_folder())
      , name_of_temp_location_to_build(NameGenerator::full_path_of_temp_location())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};




class CopySourceReleaseFilesForBuilding : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end of "name_of_source_folder"
      std::stringstream shell_command;
      shell_command << "cp -R \"" << name_of_source_folder << "\"/* \"" << name_of_temp_location_to_build << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopySourceReleaseFilesForBuilding";
   std::string name_of_source_folder;
   std::string name_of_temp_location_to_build;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopySourceReleaseFilesForBuilding()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_source_folder(NameGenerator::full_path_of_source_release_folder())
      , name_of_temp_location_to_build(NameGenerator::full_path_of_temp_location())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};





class BuildFromSourceInTempFolder : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command_1;
      shell_command_1 << "(cd " << name_of_temp_location << " && make main)";
      std::cout << shell_command_1.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command_1.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
      return Blast::String::Trimmer(shell_command_response_code).trim();
   }

public:
   static constexpr char* TYPE = (char*)"BuildFromSourceInTempFolder";
   std::string name_of_temp_location;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildFromSourceInTempFolder()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location(NameGenerator::full_path_of_temp_location())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      // TODO: fix this case where a failed build would actually return "success"
      return execute_shell_commands() == "0";
   }
};




class ValidatePresenceOfBuiltExecutable : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "(cd " << name_of_temp_location_to_build << " && ((ls \"./" << name_of_expected_executable << "\" && echo yes) || echo no))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidatePresenceOfBuiltExecutable";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfBuiltExecutable()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build(NameGenerator::full_path_of_temp_location())
      , name_of_expected_executable(NameGenerator::name_of_built_executable())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_executable + "\nyes\n")) return true;
      return false;
   }
};



#include <Blast/FileExistenceChecker.hpp>

class CopySourceAppIconPngToTempFolder : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::string source = NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG;
      std::string destination = full_destination_path_to_copied_source_icns_file;

      std::stringstream shell_command;
      shell_command << "cp \"" << source << "\" \"" << destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopySourceAppIconPngToTempFolder";
   //std::string full_path_to_source_icon_png;
   std::string full_destination_path_to_copied_source_icns_file;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopySourceAppIconPngToTempFolder()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      //, full_path_to_source_icon_png(NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG)
      , full_destination_path_to_copied_source_icns_file(NameGenerator::full_path_to_copied_source_icns_file())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n") && Blast::FileExistenceChecker(full_destination_path_to_copied_source_icns_file).exists()) return true;
      return false;
   }
};



class BuildAppIcons : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;

      // from https://stackoverflow.com/a/20703594/6072362
      // TODO: Extract icon name
      std::vector<std::string> lines = {
         "mkdir MyIcon.iconset",
         "sips -z 16 16     Icon1024.png --out MyIcon.iconset/icon_16x16.png",
         "sips -z 32 32     Icon1024.png --out MyIcon.iconset/icon_16x16@2x.png",
         "sips -z 32 32     Icon1024.png --out MyIcon.iconset/icon_32x32.png",
         "sips -z 64 64     Icon1024.png --out MyIcon.iconset/icon_32x32@2x.png",
         "sips -z 128 128   Icon1024.png --out MyIcon.iconset/icon_128x128.png",
         "sips -z 256 256   Icon1024.png --out MyIcon.iconset/icon_128x128@2x.png",
         "sips -z 256 256   Icon1024.png --out MyIcon.iconset/icon_256x256.png",
         "sips -z 512 512   Icon1024.png --out MyIcon.iconset/icon_256x256@2x.png",
         "sips -z 512 512   Icon1024.png --out MyIcon.iconset/icon_512x512.png",
         "cp Icon1024.png MyIcon.iconset/icon_512x512@2x.png",
         "iconutil -c icns MyIcon.iconset",
         "rm -R MyIcon.iconset",
      };

      std::string lines_joined = Blast::StringJoiner(lines, "\n").join();

      shell_command << "(cd " << name_of_temp_folder_for_icons << " && (" << lines_joined << "))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"BuildAppIcons";
   std::string name_of_temp_folder_for_icons;
   std::string shell_command_result;
   std::string shell_command_response_code;

   BuildAppIcons()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_folder_for_icons(TEMP_DIRECTORY_FOR_ICON)
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



class ValidatePresenceOfIcnsFile : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "(cd " << name_of_temp_location_to_build << " && ((ls \"./" << name_of_expected_generated_icns_file << "\" && echo yes) || echo no))";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ValidatePresenceOfIcnsFile";
   std::string name_of_temp_location_to_build;
   std::string name_of_expected_generated_icns_file;
   std::string shell_command_result;
   std::string shell_command_response_code;

   ValidatePresenceOfIcnsFile()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_to_build(TEMP_DIRECTORY_FOR_ICON)
      , name_of_expected_generated_icns_file(NameGenerator::built_icns_filename())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_result == ("./" + name_of_expected_generated_icns_file + "\nyes\n")) return true;
      return false;
   }
};



class CreateFoldersForReleaseAndAppPackage : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::vector<std::string> mkdir_commands;
      for (auto &folder_to_create : folders_to_create)
      {
         mkdir_commands.push_back("mkdir " + folder_to_create);
      }
      std::string mkdir_commands_chained = Blast::StringJoiner(mkdir_commands, " && ").join();

      std::stringstream shell_command;
      shell_command << "(cd " << system_releases_folder << " && (" << mkdir_commands_chained << "))";

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CreateFoldersForReleaseAndAppPackage";
   std::string system_releases_folder;
   std::vector<std::string> folders_to_create;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CreateFoldersForReleaseAndAppPackage()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , system_releases_folder(NameGenerator::SYSTEM_RELEASES_FOLDER)
      , folders_to_create(
            build_required_app_folder_names_relative_to(NameGenerator::release_folder_relative_to_system_releases_folder(), NameGenerator::name_of_executable())
            // concretion:
            //build_required_app_folder_names_relative_to("TheWeepingHouse-MacOS-chip_unknown", "TheWeepingHouse")
            // expanded concretions:
            //{
            //"TheWeepingHouse-MacOS-chip_unknown",
            //"TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app",
            //"TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents",
            //"TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS",
            //"TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources",
            //}
         )
   {}

   static std::vector<std::string> build_required_app_folder_names_relative_to(std::string relative_folder="TheWeepingHouse-MacOS-chip_unknown", std::string project_name_for_app_package="TheWeepingHouse")
   {
      std::vector<std::string> result = {
         relative_folder,                                                  // "TheWeepingHouse-MacOS-chip_unknown",
         relative_folder + "/" + project_name_for_app_package + ".app",    // "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app",
         relative_folder + "/" + project_name_for_app_package + ".app/Contents",           // "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents",
         relative_folder + "/" + project_name_for_app_package + ".app/Contents/MacOS",     // "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/MacOS",
         relative_folder + "/" + project_name_for_app_package + ".app/Contents/Resources"  // "TheWeepingHouse-MacOS-chip_unknown/TheWeepingHouse.app/Contents/Resources",
      };
      return result;
   }

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n") return true;
      return false;
   }
};



#include <Blast/TemplatedFile.hpp>

const std::string PLIST_TEMPLATE_CONTENT = R"DELIM(<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleExecutable</key>
	<string>[[NAME_OF_EXECUTABLE]]</string>
	<key>CFBundleIconFile</key>
	<string>Icon.icns</string>
	<key>CFBundleIdentifier</key>
	<string>org.markoates.[[NAME_OF_EXECUTABLE]]</string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleName</key>
	<string></string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleShortVersionString</key>
	<string>[[FULL_VERSION_NUMBER_WITH_BUILD]]</string>
	<key>CFBundleSignature</key>
	<string>????</string>
	<key>CFBundleVersion</key>
	<string>[[VERSION_NUMBER]]</string>
	<key>CSResourcesFileMapped</key>
	<true/>
	<key>LSRequiresCarbon</key>
	<true/>
	<key>NSHighResolutionCapable</key>
	<true/>
	<key>NSHumanReadableCopyright</key>
	<string>[[COPYRIGHT_TEXT]]</string>
  <key>LSMultipleInstancesProhibited</key>
  <false/>
</dict>
</plist>
)DELIM";



class CreateInfoDotPlistFile : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"CreateInfoDotPlistFile";
   std::string system_releases_folder;

   CreateInfoDotPlistFile()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , system_releases_folder(NameGenerator::SYSTEM_RELEASES_FOLDER)
      // concretion:
      //, system_releases_folder("/Users/markoates/Releases/")
   {}

   virtual bool execute() override
   {
      Blast::TemplatedFile plist_template(PLIST_TEMPLATE_CONTENT, {
            {  "[[NAME_OF_EXECUTABLE]]",  NameGenerator::NAME_OF_EXECUTABLE},
            {  "[[COPYRIGHT_TEXT]]",      NameGenerator::COPYRIGHT_FULL_TEXT },
            {  "[[FULL_VERSION_NUMBER_WITH_BUILD]]", NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD },
            {  "[[VERSION_NUMBER]]", NameGenerator::VERSION_NUMBER },
         });

      std::string full_path_and_filename = NameGenerator::full_path_to_result_info_dot_plist_file();
      file_put_contents(full_path_and_filename, plist_template.generate_content());

      return Blast::FileExistenceChecker(full_path_and_filename).exists();
   }
};



class ValidateSourceReadme : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidateSourceReadme";
   std::string full_location_to_source_readme_file;

   ValidateSourceReadme()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source_readme_file(NameGenerator::full_path_to_source_readme())
   {}

   virtual bool execute() override
   {
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "ValidateSourceReadme:" << std::endl;
      std::cout << "  looking for: \"" << full_location_to_source_readme_file << "\"" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      return Blast::FileExistenceChecker(full_location_to_source_readme_file).exists();
   }
};



class ValidatePresenceOfAppInfoFile : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidatePresenceOfAppInfoFile";
   std::string full_location_to_source_app_info_file;

   ValidatePresenceOfAppInfoFile()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source_app_info_file(NameGenerator::full_path_to_source_app_info_file())
   {}

   virtual bool execute() override
   {
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "ValidatePresenceOfAppInfoFile:" << std::endl;
      std::cout << "  looking for: \"" <<  full_location_to_source_app_info_file << "\"" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      return Blast::FileExistenceChecker( full_location_to_source_app_info_file).exists();
   }
};



class ValidateAndSetAppIconFilename : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidateAndSetAppIconFilename";
   std::string full_location_to_source_app_info_file;

   ValidateAndSetAppIconFilename()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source_app_info_file(NameGenerator::full_path_to_source_app_info_file())
   {}

   virtual bool execute() override
   {
      // HERE
      Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
      std::string file_contents = file_get_contents(full_location_to_source_app_info_file);
      source_release_app_info_file.load_contents(file_contents);

      std::string app_icon_filename = source_release_app_info_file.get_app_icon_filename();
      std::string final_full_path = NameGenerator::full_path_of_temp_location() + app_icon_filename;

      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "ValidateAndSetAppIconFilename:" << std::endl;
      std::cout << "  Found app icon filename: \"" <<  app_icon_filename << "\"" << std::endl;
      std::cout << "  Assuming path: \"" << NameGenerator::full_path_of_temp_location() << "\"";
      std::cout << "  Final FULL_PATH_TO_SOURCE_ICON_PNG: \"" << final_full_path << "\"";
      std::cout << std::endl;
      std::cout << std::endl;

      NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG = final_full_path;
      return true;
   }
};



class GenerateBuildInfoCppFileInTempSrcFolder : public Blast::BuildSystem::BuildStages::Base
{
private:
   void generate_and_create_file()
   {
      Blast::BuildInfo build_info = Blast::BuildInfoBuilder().build();

      // Assign the build time
      build_info.set_time_of_build(time_of_build_string);

      // Generate and create the file
      Blast::BuildInfoCppFileGenerator build_info_cpp_file_generator(build_info);
      build_info_cpp_file_generator.initialize();
      std::string target_build_info_filename = name_of_temp_location_with_build + "src/BuildInfo.cpp"; // TODO: Move this filename up to the NameGenerator
      file_was_created_successfully = file_put_contents(target_build_info_filename, build_info_cpp_file_generator.source_file_content());
   }

public:
   static constexpr char* TYPE = (char*)"GenerateBuildInfoCppFileInTempSrcFolder";
   std::string name_of_temp_location_with_build;
   std::string time_of_build_string;
   bool file_was_created_successfully;

   GenerateBuildInfoCppFileInTempSrcFolder()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_with_build(NameGenerator::full_path_of_temp_location())
      , time_of_build_string(NameGenerator::get_time_of_build_string())
      , file_was_created_successfully(false)
   {}

   virtual bool execute() override
   {
      generate_and_create_file();
      return file_was_created_successfully;
   }
};



class CopyBuiltBinaryToAppPackage : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::string source = name_of_temp_location_with_build + name_of_built_executable;
      std::string destination = NameGenerator::full_binary_app_package_destination();

      std::stringstream shell_command;
      shell_command << "cp \"" << source << "\" \"" << destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyBuiltBinaryToAppPackage";
   std::string name_of_temp_location_with_build;
   std::string name_of_built_executable;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyBuiltBinaryToAppPackage()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , name_of_temp_location_with_build(NameGenerator::full_path_of_temp_location())
      , name_of_built_executable(NameGenerator::name_of_built_executable())
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



#include <Blast/DirectoryExistenceChecker.hpp>

class CopyDataFolderToAppPackage : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      //TODO: require '/' character at end
      std::stringstream shell_command;
      shell_command << "cp -R \"" << full_path_of_source_data_folder << "\" \"" << full_path_of_app_package_destination_folder << "\"";
      std::cout << shell_command.str() << std::endl;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyDataFolderToAppPackage";
   std::string full_path_of_source_data_folder;
   std::string full_path_of_app_package_destination_folder;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyDataFolderToAppPackage()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_of_source_data_folder(NameGenerator::full_path_of_source_data_folder())
      , full_path_of_app_package_destination_folder(NameGenerator::full_path_of_destination_data_folder())
      , shell_command_result()
      , shell_command_response_code()
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == "0\n" && Blast::DirectoryExistenceChecker(full_path_of_app_package_destination_folder).exists()) return true;
      return false;
   }
};




class CopyIcnsFileToAppPackage : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "cp \"" << full_source_location_of_icns_file << "\" \"" << full_destination_location << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyIcnsFileToAppPackage";
   std::string full_source_location_of_icns_file;
   std::string full_destination_location;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyIcnsFileToAppPackage()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_source_location_of_icns_file(NameGenerator::full_path_to_built_icns_file())
      , full_destination_location(NameGenerator::full_path_to_destination_icns_file())
   {}

   virtual bool execute() override
   {
      // TODO: validate existence of file
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



class CopyReadmeFileToRelaseFolder : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "cp \"" << full_location_to_source << "\" \"" << full_location_to_destination << "\"";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CopyReadmeFileToRelaseFolder";
   std::string full_location_to_source;
   std::string full_location_to_destination;
   std::string shell_command_result;
   std::string shell_command_response_code;

   CopyReadmeFileToRelaseFolder()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_location_to_source(NameGenerator::full_path_to_source_readme())
      , full_location_to_destination(NameGenerator::full_path_to_destination_readme())
   {}

   virtual bool execute() override
   {
      // TODO: validate existence of file
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};





class DetectPresenceOfExtendedAttributesAndRemoveIfPresent : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"DetectPresenceOfExtendedAttributesAndRemoveIfPresent";
   //std::string shell_command_result;

   DetectPresenceOfExtendedAttributesAndRemoveIfPresent()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      // For this process, see https://developer.apple.com/library/archive/qa/qa1940/_index.html
      std::string release_folder_location = NameGenerator::release_folder_location();
      std::string app_package_folder_name = NameGenerator::app_package_folder_name();

      std::cout << "============================================ detecting extended attributes (start) =================================================" << std::endl;
      std::stringstream detect_extended_attributes_shell_command;
         detect_extended_attributes_shell_command << "(cd " << release_folder_location << " && xattr -lr " << app_package_folder_name << ")";
      Blast::ShellCommandExecutorWithCallback detect_shell_command_executor(detect_extended_attributes_shell_command.str());
      std::string detect_extended_attributes_shell_command_result = detect_shell_command_executor.execute();
      std::cout << "============================================ detecting extended attributes (dump result) =================================================" << std::endl;
      std::cout << detect_extended_attributes_shell_command_result << std::endl;
      std::cout << "============================================ detecting extended attributes (end) =================================================" << std::endl;

      std::cout << "============================================ removing extended attributes (start) =================================================" << std::endl;
      std::stringstream remove_extended_attributes_shell_command;
         remove_extended_attributes_shell_command << "(cd " << release_folder_location << " && xattr -cr " << app_package_folder_name << ")";
      Blast::ShellCommandExecutorWithCallback remove_shell_command_executor(remove_extended_attributes_shell_command.str());
      std::string remove_extended_attributes_shell_command_result = remove_shell_command_executor.execute();
      std::cout << "============================================ detecting extended attributes (dump result) =================================================" << std::endl;
      std::cout << remove_extended_attributes_shell_command_result << std::endl;
      std::cout << "============================================ detecting extended attributes (end) =================================================" << std::endl;

      return true;
   }
};



class BuildAndBundleDylibsWithAppPackage : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string cout_temp_file;
   std::string temp_file_contents()
   {
      return trim(file_get_contents(cout_temp_file));
   }

   void execute_shell_commands()
   {
      cout_temp_file = build_temp_filename();

      std::cout << "============== DYLIB =================" << std::endl;

      std::string release_folder_location = NameGenerator::release_folder_location();
      std::string app_package_folder_name = NameGenerator::app_package_folder_name();
      std::string app_package_executable_name = NameGenerator::app_package_executable_name();
      std::stringstream shell_command;
      shell_command << "(cd " << release_folder_location << " && (export DYLD_LIBRARY_PATH=/usr/local/lib" << std::endl
                    << "dylibbundler -x \"" << app_package_folder_name << "/Contents/MacOS/" << app_package_executable_name << "\" -b -d \"" << app_package_folder_name << "/Contents/MacOS\" -p @executable_path -s $DYLD_LIBRARY_PATH"
                    << ")) && (echo $? > " << cout_temp_file << ")";

      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      std::cout << "============ DYLIB ENDS ==============" << std::endl;

      //Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      //shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"BuildAndBundleDylibsWithAppPackage";
   std::string shell_command_result;
   //std::string shell_command_response_code;

   BuildAndBundleDylibsWithAppPackage()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (temp_file_contents() == "0") return true;
      return false;
      //if (shell_command_response_code == ("0\n")) return true;
      //return false;
   }
};




class CreateZipFromReleaseFolder : public Blast::BuildSystem::BuildStages::Base
{
private:
   void execute_shell_commands()
   {
      std::stringstream shell_command;
      shell_command << "(cd " << NameGenerator::SYSTEM_RELEASES_FOLDER  << " && (zip -r \"" << NameGenerator::release_zip_filename() << "\" \"" << NameGenerator::release_folder_relative_to_system_releases_folder() << "\"))";
      std::cout << shell_command.str() << std::endl;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      shell_command_result = shell_command_executor.execute();

      Blast::ShellCommandExecutorWithCallback shell_command_executor2("echo $?");
      shell_command_response_code = shell_command_executor2.execute();
   }

public:
   static constexpr char* TYPE = (char*)"CreateZipFromReleaseFolder";
   std::string shell_command_result;
   std::string shell_command_response_code;

   CreateZipFromReleaseFolder()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
   {}

   virtual bool execute() override
   {
      execute_shell_commands();
      if (shell_command_response_code == ("0\n")) return true;
      return false;
   }
};



#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <filesystem>

std::filesystem::path create_temporary_directory(unsigned long long max_tries = 100000)
{
    auto tmp_dir = std::filesystem::temp_directory_path();
    unsigned long long i = 0;
    std::random_device dev;
    std::mt19937 prng(dev());
    std::uniform_int_distribution<uint64_t> rand(0);
    std::filesystem::path path;
    while (true) {
        std::stringstream ss;
        ss << std::hex << rand(prng);
        path = tmp_dir / ss.str();
        // true if the directory was created.
        if (std::filesystem::create_directory(path)) {
            break;
        }
        if (i == max_tries) {
            throw std::runtime_error("could not find non-existing directory");
        }
        i++;
    }
    return path;
}



int main(int argc, char **argv)
{
   // TODO: Warn the builder if allegro repo is not master
   // TODO: Warn the builder if allegro has dirty worktree files
   // TODO: Warn the builder if allegro hash does not match the version used to create the release

   // TODO: Warn the builder if allegro_flare repo is not master
   // TODO: Warn the builder if allegro_flare has dirty worktree files
   // TODO: Warn the builder if allegro_flare hash does not match the version used to create the release

   Blast::SystemInfo system_info;

   if (!system_info.is_apple_mac())
   {
      std::cout << std::endl;
      std::cout << "Oops! This program is not intended to be run on a non-mac machine." << std::endl;
      std::cout << "The Blast::SystemInfo detected that this is a non-MacOS system" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "   Expecting: " << Blast::SystemInfo::MACOS_SYSNAME << std::endl;
      std::cout << "         Got: " << system_info.get_sysname() << std::endl;
      std::cout << std::endl;
      return 1;
   }


   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   std::string arg_name_of_executable = "Krampus22_test1"; // This needs to match the name of the project in the source release folder.
                                                           // note that this name is set by the generated Makefile and will match the
                                                           // name of the projcet.
   std::string arg_source_release_folder_name = "Krampus22_test1-SourceRelease-221209191155UTC";
   std::string arg_source_version_string = "1.2.3"; // This needs to match the name of the project in the source release folder.
                                                    // note that this name is set by the generated Makefile and will match the
                                                    // name of the projcet.


   if (args.size() == 4)
   {
      arg_name_of_executable = args[1];
      // TODO: validate version string
      arg_source_version_string = args[2];
      arg_source_release_folder_name = args[3];
   }
   else
   {
      // TODO: Improve this error message
      std::cout << std::endl;
      std::cout << "You need to pass a few arguments, like this:" << std::endl;
      std::cout << std::endl;
      std::cout << "    ./bin/programs/macos_release_builder [project_name] [version_number] [expected_folder_in_source_release]" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "For example:" << std::endl;
      std::cout << std::endl;
      std::cout << "    ./bin/programs/macos_release_builder TheWeepingHouse 1.2.3 TheWeepingHouse-1.2.3-SourceRelease" << std::endl;
      std::cout << std::endl;
      return 2;
   }



   NameGenerator::START_TIME_OF_BUILD = std::chrono::system_clock::now();


   std::cout << "Building with the folowing information:" << std::endl;
   std::cout << "   Source release folder name: \"" << arg_source_release_folder_name << "\"" << std::endl;
   std::cout << "           Name of executable: \"" << arg_name_of_executable << "\"" << std::endl;
   std::cout << "                      Version: \"" << arg_source_version_string  << "\"" << std::endl;

   //std::filesystem::path temporary_directory1 = create_temporary_directory();
   //std::filesystem::path temporary_directory2 = create_temporary_directory();

   TEMP_DIRECTORY_FOR_BUILD = create_temporary_directory().string();
   TEMP_DIRECTORY_FOR_ICON = create_temporary_directory().string();
   TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD = create_temporary_directory().string();



   //std::string name_of_app_info_file = Blast::Project::SourceReleaseAppInfoFile::APP_INFO_FILENAME; // Right now, "app.info", might change later




   std::cout << "=== TEMP_DIRECTORY_FOR_BUILD ===" << std::endl;
   std::cout << TEMP_DIRECTORY_FOR_BUILD << std::endl;
   std::cout << "=== TEMP_DIRECTORY_FOR_ICON ===" << std::endl;
   std::cout << TEMP_DIRECTORY_FOR_ICON << std::endl;
   std::cout << "=== TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD ===" << std::endl;
   std::cout << TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD << std::endl;



   NameGenerator::SYSTEM_RELEASES_FOLDER = "/Users/markoates/Releases/"; // NOTE, must end in "/"; TODO: validate ending in "/"
   NameGenerator::SOURCE_RELEASE_FOLDER_NAME //= "TheWeepingHouse-SourceRelease-220903200818UTC";
                                             //= "TheWeepingHouse-SourceRelease-221209175604UTC";
                                             //= "Krampus22_test1-SourceRelease-221209181637UTC";
                                             //= "Krampus22_test1-SourceRelease-221209191155UTC";
                                             = arg_source_release_folder_name;

                                             //221209180525UTC";

   NameGenerator::NAME_OF_EXECUTABLE //= "Krampus22_test1"; // This needs to match the name of the project in the source release folder.
                                                          // note that this name is set by the generated Makefile and will match the
                                                          // name of the projcet.
                                     = arg_name_of_executable;
   //NameGenerator::NAME_OF_EXECUTABLE = "TheWeepingHouse";
   NameGenerator::COPYRIGHT_FULL_TEXT = "Copyright 2022 - Mark Oates - www.CLUBCATT.com";
   NameGenerator::FULL_VERSION_NUMBER_WITH_BUILD = arg_source_version_string; //"1.0.0.3";
   NameGenerator::VERSION_NUMBER = arg_source_version_string; //"1.0.0";
   // TODO: consider moving this static location for the default icon, also only use it as a fallback if the repo does not have an app icon
   NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG = "[icon-file-is-not-set]"; //"/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/allegro-flare-generic-icon-1024.png";
   //NameGenerator::FULL_PATH_TO_SOURCE_ICON_PNG = "/Users/markoates/Releases/" + NameGenerator::SOURCE_RELEASE_FOLDER_NAME + "/data/system/allegro-flare-generic-icon-1024.png";
   NameGenerator::TEMP_DIRECTORY_FOR_BUILD = TEMP_DIRECTORY_FOR_BUILD;
   NameGenerator::TEMP_DIRECTORY_FOR_ICON = TEMP_DIRECTORY_FOR_ICON;
   NameGenerator::TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD = TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD;
   NameGenerator::CHIP_NAME = system_info.get_processor_type();



   // TODO: assign this:
   //NameGenerator::FULL_PATH_TO_LOCAL_DESTINATION_OF_ZIP_FILE = TEMP_DIRECTORY_FOR_ZIP_DOWNLOAD + "/" + arg_source_release_folder_name + ".zip"
   //NameGenerator::FULL_URL_OF_FILE_TO_DOWNLOAD;




   Blast::BuildSystem::BuildStageFactory build_stage_factory;
   Blast::BuildSystem::Builds::Base *build = new Blast::BuildSystem::Builds::Base;
   build->set_build_stages({
      //new CopySourceAppIconPngToTempFolder(),

      // validate these are present
      new ValidateDylibBundlerVersion(),
      new ValidateXattrVersion(),
      new ValidateIconutil(),
      new ValidateSips(),
      new ValidateZip(),
      new ValidateCurl(),
      new ValidateUnzip(),

      // get copy of source release (either from copying the source release files or downloading)...

      // ... this is an option if is local:
      //new CopySourceReleaseFilesForBuilding(),

      // ... this is the option if it's remote
      new VerifySourceReleaseZipFileIsAvailableForDownloading(),
      new DownloadSourceReleaseFileForBuilding(),
      new UnzipDownloadedSourceReleaseFile(),
      new CopyUnzippedSourceReleaseFilesToTemporaryDirectoryForBuild(),

      // validate README.md in source
      new ValidateSourceReadme(),

      // TODO: Validate app info file exists
      new ValidatePresenceOfAppInfoFile(),

      // TODO: Validate source icon filename is present in the app info file, assign to global
      new ValidateAndSetAppIconFilename(),

      // generate a src/BuildInfo.cpp file
      new GenerateBuildInfoCppFileInTempSrcFolder(),

      // make a build from the source
      new BuildFromSourceInTempFolder(),
      new ValidatePresenceOfBuiltExecutable(),

      // Make the app package
      // TODO: copy the source's app icon png into the temp location to build the icns file
      new CopySourceAppIconPngToTempFolder(),
      new BuildAppIcons(),
      new ValidatePresenceOfIcnsFile(),
      new CreateFoldersForReleaseAndAppPackage(),
      new CreateInfoDotPlistFile(),
      new CopyBuiltBinaryToAppPackage(),
      new CopyDataFolderToAppPackage(),
      new CopyIcnsFileToAppPackage(),
      new CopyReadmeFileToRelaseFolder(),
      new DetectPresenceOfExtendedAttributesAndRemoveIfPresent(),
      new BuildAndBundleDylibsWithAppPackage(), // TODO: this process can error but it will not report an error

      // Zip it up and prepare it for launch
      new CreateZipFromReleaseFolder(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();





   Blast::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;



   if (!build->finished_successfully())
   {
      std::stringstream failure_message;
      failure_message << std::endl;
      failure_message << "///////////////////////////////////////////////////////////" << std::endl;
      failure_message << "///      MacOS build did not complete successfully      ///" << std::endl;
      failure_message << "///////////////////////////////////////////////////////////" << std::endl;
      failure_message << std::endl;
      failure_message << "See the report above to find out where the build failed." << std::endl;
      failure_message << std::endl;
      failure_message << std::endl;
      std::cout << CONSOLE_COLOR_YELLOW << failure_message.str() << CONSOLE_COLOR_DEFAULT << std::endl;
   }
   else 
   {
      std::string generated_source_release_zip_filename = NameGenerator::release_zip_filename();
      std::stringstream success_message;

      success_message << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << "==     MacOS build finished successfully!    ==" << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << std::endl;
      //success_message << "                   ~Releases base folder: \"" << destination_directory << "\"" << std::endl;
      //success_message << "   Command to go to the ~Releases folder: \"cd " << destination_directory << "\"" << std::endl;
      //success_message << "                     Release folder name: \"" << generated_release_folder_name << "\"" << std::endl;
      //success_message << "                        Release zip file: \"" << generated_source_release_zip_filename << "\"" << std::endl;
      //success_message << std::endl;
      //success_message << "Note that a zip file was automatically crated.  The following command can be used to zip it up if you wish to modify the folder and re-zip it:" << std::endl;
      //success_message << std::endl;
      //success_message << "(cd " << destination_directory << " && rm " << generated_source_release_zip_filename << ")" << std::endl;
      //success_message << "(cd " << destination_directory << "/" << generated_release_folder_name << " && rm -rdf " << project_testing_src_folder_name.str() << ")" << std::endl;
      //success_message << "(cd " << destination_directory << "/" << generated_release_folder_name << " && rm -rdf " << project_testing_include_folder_name.str() << ")" << std::endl;
      //success_message << "zip -r " << generated_source_release_zip_filename << " " << generated_release_folder_name << std::endl;
      success_message << std::endl;
      success_message << "If you wish to upload the file to a bucket on google cloud, run the following command:" << std::endl;
      success_message << "gcloud storage cp ~/Releases/" << generated_source_release_zip_filename << " gs://clubcatt-games-bucket/" << std::endl;
      success_message << std::endl;
      success_message << "Your zip release file should then be available on the web at:" << std::endl;
      success_message << "https://storage.googleapis.com/clubcatt-games-bucket/" << generated_source_release_zip_filename << std::endl;
      success_message << std::endl;
      success_message << "For help setting up gcloud, then please reference me/installing_and_setting_up_google_cloud.md" << std::endl;
      success_message << std::endl;
      success_message << std::endl;
      //success_message << std::endl;
      //success_message << "===============================================" << std::endl;
      //success_message << "==          Create Binary Releases           ==" << std::endl;
      //success_message << "===============================================" << std::endl;
      //success_message << std::endl;
      //success_message << "   Command to make MacOS release: \"" << command_to_make_macos_release.str() << "\"" << std::endl;
      //success_message << "   Command to make Win64 release: \"" << command_to_make_win64_release.str() << "\"" << std::endl;
      //success_message << std::endl;
      std::cout << CONSOLE_COLOR_CYAN << success_message.str() << CONSOLE_COLOR_DEFAULT << std::endl;
   }


   return 0;
}
