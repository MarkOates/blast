#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class Win64ReleaseBuilder
      {
      private:
         std::string projects_folder;
         std::string win64_release_builder_shell_script_filename;

      protected:


      public:
         Win64ReleaseBuilder(std::string projects_folder="/Users/markoates/Repos/");
         ~Win64ReleaseBuilder();

         std::string build_full_path_to_win64_release_builder_script();
         void run();
      };
   }
}



