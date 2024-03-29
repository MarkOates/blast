#pragma once


#include <cstdint>
#include <string>


namespace Blast
{
   class SystemInfo
   {
   public:
      static constexpr char* MACOS_SYSNAME = (char*)"Darwin";

   private:

   protected:


   public:
      SystemInfo();
      ~SystemInfo();

      uint32_t num_available_threads();
      bool num_available_threads_are_known();
      std::string get_processor_type();
      std::string get_sysname();
      bool is_apple_mac();
      bool is_microsoft_windows();
      std::string get_version();
      std::string get_release();
      std::string get_hostname();
      std::string get_machine();
      std::string operating_system();
   };
}



