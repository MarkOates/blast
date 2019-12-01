

#include <Blast/TemplatedFile.hpp>



namespace Blast
{


TemplatedFile::TemplatedFile(std::string template_content, std::vector<std::pair<std::string, std::string>> insertion_variables)
   : template_content(template_content)
   , insertion_variables(insertion_variables)
{
}


TemplatedFile::~TemplatedFile()
{
}


std::string TemplatedFile::generate_content()
{
return "Hello, World!";

}
} // namespace Blast


