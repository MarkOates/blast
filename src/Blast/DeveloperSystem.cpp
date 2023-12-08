

#include <Blast/DeveloperSystem.hpp>

#include <Blast/Errors.hpp>
#include <Blast/SystemInfo.hpp>


namespace Blast
{


DeveloperSystem::DeveloperSystem()
   : macos_project_directory(DEFAULT_MACOS_PROJECT_DIRECTORY)
   , microsoft_windows_project_directory(DEFAULT_MICROSOFT_WINDOWS_PROJECT_DIRECTORY)
{
}


DeveloperSystem::~DeveloperSystem()
{
}


void DeveloperSystem::set_macos_project_directory(std::string macos_project_directory)
{
   this->macos_project_directory = macos_project_directory;
}


void DeveloperSystem::set_microsoft_windows_project_directory(std::string microsoft_windows_project_directory)
{
   this->microsoft_windows_project_directory = microsoft_windows_project_directory;
}


std::string DeveloperSystem::get_macos_project_directory() const
{
   return macos_project_directory;
}


std::string DeveloperSystem::get_microsoft_windows_project_directory() const
{
   return microsoft_windows_project_directory;
}


std::string DeveloperSystem::infer_project_directory()
{
   Blast::SystemInfo system_info;
   if (system_info.is_microsoft_windows()) return microsoft_windows_project_directory;
   else if (system_info.is_apple_mac()) return macos_project_directory;

   Blast::Errors::throw_error(
      "Blast::DeveloperSystem::infer_project_directory",
      "Could not infer the type of system (windows/mac)"
   );

   return "";
}


} // namespace Blast


