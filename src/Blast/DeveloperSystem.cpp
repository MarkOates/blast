

#include <Blast/DeveloperSystem.hpp>

#include <Blast/Errors.hpp>
#include <Blast/SystemInfo.hpp>


namespace Blast
{


DeveloperSystem::DeveloperSystem()
   : macos_base_directory(DEFAULT_MACOS_BASE_DIRECTORY)
   , microsoft_windows_base_directory(DEFAULT_MICROSOFT_WINDOWS_BASE_DIRECTORY)
{
}


DeveloperSystem::~DeveloperSystem()
{
}


void DeveloperSystem::set_macos_base_directory(std::string macos_base_directory)
{
   this->macos_base_directory = macos_base_directory;
}


void DeveloperSystem::set_microsoft_windows_base_directory(std::string microsoft_windows_base_directory)
{
   this->microsoft_windows_base_directory = microsoft_windows_base_directory;
}


std::string DeveloperSystem::get_macos_base_directory() const
{
   return macos_base_directory;
}


std::string DeveloperSystem::get_microsoft_windows_base_directory() const
{
   return microsoft_windows_base_directory;
}


std::string DeveloperSystem::infer_base_directory()
{
   Blast::SystemInfo system_info;
   if (system_info.is_microsoft_windows()) return microsoft_windows_base_directory;
   else if (system_info.is_apple_mac()) return macos_base_directory;

   Blast::Errors::throw_error(
      "Blast::DeveloperSystem::infer_base_directory",
      "Could not infer the type of system (windows/mac)"
   );

   return "";
}

std::string DeveloperSystem::infer_project_directory()
{
   // project? projects? repos?
   return infer_base_directory() + DEFAULT_PROJECT_DIRECTORY;
}

std::string DeveloperSystem::infer_builds_directory()
{
   return infer_base_directory() + DEFAULT_BUILDS_DIRECTORY;
}


} // namespace Blast


