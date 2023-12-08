#pragma once


#include <string>


namespace Blast
{
   class DeveloperSystem
   {
   public:
      static constexpr const char* DEFAULT_MACOS_BASE_DIRECTORY = (char*)"/Users/markoates/";
      static constexpr const char* DEFAULT_MICROSOFT_WINDOWS_BASE_DIRECTORY = (char*)"/msys64/home/Mark/";
      static constexpr const char* DEFAULT_PROJECT_DIRECTORY = (char*)"Repos/";
      static constexpr const char* DEFAULT_BUILDS_DIRECTORY = (char*)"Builds/";

   private:
      std::string macos_base_directory;
      std::string microsoft_windows_base_directory;

   protected:


   public:
      DeveloperSystem();
      ~DeveloperSystem();

      void set_macos_base_directory(std::string macos_base_directory);
      void set_microsoft_windows_base_directory(std::string microsoft_windows_base_directory);
      std::string get_macos_base_directory() const;
      std::string get_microsoft_windows_base_directory() const;
      std::string infer_base_directory();
      std::string infer_projects_directory();
      std::string infer_builds_directory();
   };
}



