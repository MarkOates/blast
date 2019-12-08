

#include <Blast/Project/Component.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>


namespace Blast
{
namespace Project
{


Component::Component(std::string name)
   : name(name)
{
}


Component::~Component()
{
}


std::string Component::get_name()
{
   return name;
}


bool Component::check_file_existence(Blast::ProjectComponentFileTypes::project_file_type_t type)
{
std::string filename = Blast::ProjectComponentFilenameGenerator(name, type).generate_filename();
return Blast::FileExistenceChecker(filename).exists();

}

bool Component::has_quintessence()
{
return check_file_existence(Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE);

}
} // namespace Project
} // namespace Blast


