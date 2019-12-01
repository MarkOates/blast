#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class TemplatedFile
   {
   private:
      std::string template_content;
      std::vector<std::pair<std::string, std::string>> insertion_variables;

   public:
      TemplatedFile(std::string template_content="[[GREETING]], [[SUBJECT]]!", std::vector<std::pair<std::string, std::string>> insertion_variables={ { "GREETING", "Hello" }, { "SUBJECT", "World" } });
      ~TemplatedFile();


   std::string generate_content();
   };
}



