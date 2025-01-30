#pragma once


#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class CodeUsageScanner
      {
      private:
         std::string project_directory;
         static std::vector<std::string> remove_empty(std::vector<std::string> strVector={});

      protected:


      public:
         CodeUsageScanner(std::string project_directory="/Users/markoates/Repos/SomePlatformer");
         ~CodeUsageScanner();

         void set_project_directory(std::string project_directory);
         std::string get_project_directory() const;
         std::pair<bool, std::string> build_report();
         bool token_exists_in_file(std::string filename="path/to/file.cpp", std::string search_token="#include <cmath>");
         std::string build_scan_shell_command(std::string search_token="std::vector");
         std::string obtain_required_header_for_token(std::string token="[unset-token]");
         std::unordered_map<std::string, std::string> build_common_required_headers_list();
         static std::vector<std::pair<std::string, std::string>> tokenize_lines(std::vector<std::string>* lines=nullptr);
         static std::string sanitize_search_token(std::string search_token="std::vector");
         static std::string build_comma_separated_unique_asset_identifier_list(std::vector<std::pair<std::string, std::string>>* asset_studio_data=nullptr, std::string separator=" ");
         static std::vector<std::pair<std::string, std::string>> extract_code_studio_data(std::vector<std::string>* lines=nullptr);
         std::pair<bool, std::vector<std::string>> check_for_prefixed_assets();
         static std::vector<std::string> trim_each(std::vector<std::string> tokens={});
      };
   }
}



