#pragma once


#include <string>


namespace Blast
{
   class DeveloperSystem
   {
   public:
      static constexpr const char* DEFAULT_MACOS_PROJECT_DIRECTORY = (char*)"/Users/markoates/Repos/";
      static constexpr const char* DEFAULT_MICROSOFT_WINDOWS_PROJECT_DIRECTORY = (char*)"/msys64/home/Mark/Repos/";

   private:
      std::string macos_project_directory;
      std::string microsoft_windows_project_directory;

   protected:


   public:
      DeveloperSystem();
      ~DeveloperSystem();

      void set_macos_project_directory(std::string macos_project_directory);
      void set_microsoft_windows_project_directory(std::string microsoft_windows_project_directory);
      std::string get_macos_project_directory() const;
      std::string get_microsoft_windows_project_directory() const;
      std::string infer_project_directory();
   };
}



