#pragma once


#include <Blast/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      class ReportRenderer
      {
      private:
         Blast::BuildSystem::Builds::Base* build;

      protected:


      public:
         ReportRenderer(Blast::BuildSystem::Builds::Base* build=nullptr);
         ~ReportRenderer();

         void set_build(Blast::BuildSystem::Builds::Base* build);
         Blast::BuildSystem::Builds::Base* get_build() const;
         std::string build_text_report();
      };
   }
}



