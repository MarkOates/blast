#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class FunctionBody
      {
      public:
         static constexpr char* DEFAULT_BODY_CONTENT = (char*)"return;";

      private:
         std::string content;
         std::vector<std::string> dependency_symbols;

      protected:


      public:
         FunctionBody(std::string content=DEFAULT_BODY_CONTENT, std::vector<std::string> dependency_symbols={});
         ~FunctionBody();

         void set_content(std::string content);
         void set_dependency_symbols(std::vector<std::string> dependency_symbols);
         std::string get_content() const;
         std::vector<std::string> get_dependency_symbols() const;
      };
   }
}



