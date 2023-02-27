

#include <Blast/SystemInfo.hpp>

#include <Blast/SystemInfoFetcher.hpp>
#include <thread>


namespace Blast
{


SystemInfo::SystemInfo()
{
}


SystemInfo::~SystemInfo()
{
}


uint32_t SystemInfo::num_available_threads()
{
   return std::thread::hardware_concurrency();
}

bool SystemInfo::num_available_threads_are_known()
{
   return (std::thread::hardware_concurrency() != 0);
}

std::string SystemInfo::get_processor_type()
{
   std::string machine = get_machine();
   if (machine.empty()) return "[unable-to-detect]";
   if (machine.substr(0, 3) == "arm") return "arm";
   if (machine.substr(0, 3) == "x86" && operating_system() == "MacOS") return "intel";
   return "[chip-kind-not-detected]";
}

std::string SystemInfo::get_sysname()
{
   return Blast::SystemInfoFetcher().get_sysname();
}

bool SystemInfo::is_apple_mac()
{
   // TODO: find a way to test this
   return get_sysname() == "Darwin";
}

bool SystemInfo::is_microsoft_windows()
{
   // TODO: find a way to test this
   std::string sysname = get_sysname();
   std::string starts_with_string = "Windows";
   bool starts_with_expected_string = (sysname.compare(0, starts_with_string.length(), starts_with_string) == 0);
   return starts_with_expected_string;
}

std::string SystemInfo::get_version()
{
   return Blast::SystemInfoFetcher().get_version();
}

std::string SystemInfo::get_release()
{
   return Blast::SystemInfoFetcher().get_release();
}

std::string SystemInfo::get_hostname()
{
   return Blast::SystemInfoFetcher().get_hostname();
}

std::string SystemInfo::get_machine()
{
   return Blast::SystemInfoFetcher().get_machine();
}

std::string SystemInfo::operating_system()
{
   // TODO: this might be incorrect, might be detecting WIN32 even when WIN64 is present

   #ifdef _WIN32
   return "Windows 32-bit";
   #elif _WIN64
   return "Windows 64-bit";
   #elif __APPLE__ || __MACH__
   return "MacOS";
   #elif __linux__
   return "Linux";
   #elif __FreeBSD__
   return "FreeBSD";
   #elif __unix || __unix__
   return "Unix";
   #else
   return "Other";
   #endif
}


} // namespace Blast


