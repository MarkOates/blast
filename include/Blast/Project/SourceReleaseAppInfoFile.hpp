#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class SourceReleaseAppInfoFile
      {
      public:
         static constexpr const char* APP_INFO_FILENAME = (char*)"app.info";
         static constexpr const char* DEFAULT_APP_ICON_FILENAME = (char*)"data/icons/allegro-flare-generic-icon-1024.png";

      private:
         std::string app_icon_filename;

      protected:


      public:
         SourceReleaseAppInfoFile(std::string app_icon_filename=DEFAULT_APP_ICON_FILENAME);
         ~SourceReleaseAppInfoFile();

         void set_app_icon_filename(std::string app_icon_filename);
         std::string get_app_icon_filename() const;
         bool app_icon_filename_is_default();
         std::string get_contents();
         void load_contents(std::string raw_contents="[unset-raw_contents]");
         static std::vector<std::string> trim_each(std::vector<std::string> tokens={});
      };
   }
}



