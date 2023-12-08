#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class SourceReleaseAppInfoFile
      {
      private:
         std::string app_icon_filename;

      protected:


      public:
         SourceReleaseAppInfoFile(std::string app_icon_filename="bin/data/icons/allegro-flare-generic-icon-1024.png");
         ~SourceReleaseAppInfoFile();

         void set_app_icon_filename(std::string app_icon_filename);
         std::string get_app_icon_filename() const;
         std::string get_contents();
         void load_contents(std::string raw_contents="[unset-raw_contents]");
         static std::vector<std::string> trim_each(std::vector<std::string> tokens={});
      };
   }
}



