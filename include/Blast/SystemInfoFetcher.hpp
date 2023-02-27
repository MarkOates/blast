#pragma once


#include <string>


namespace Blast
{
   class SystemInfoFetcher
   {
   public:
      SystemInfoFetcher();
      ~SystemInfoFetcher();

      std::string get_sysname();
      std::string get_version();
      std::string get_release();
      std::string get_machine();
      std::string get_hostname();
   };
}


