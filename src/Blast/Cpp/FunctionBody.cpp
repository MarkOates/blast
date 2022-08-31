

#include <Blast/Cpp/FunctionBody.hpp>




namespace Blast
{
namespace Cpp
{


FunctionBody::FunctionBody(std::string content, std::vector<std::string> dependency_symbols)
   : content(content)
   , dependency_symbols(dependency_symbols)
{
}


FunctionBody::~FunctionBody()
{
}


void FunctionBody::set_content(std::string content)
{
   this->content = content;
}


void FunctionBody::set_dependency_symbols(std::vector<std::string> dependency_symbols)
{
   this->dependency_symbols = dependency_symbols;
}


std::string FunctionBody::get_content() const
{
   return content;
}


std::vector<std::string> FunctionBody::get_dependency_symbols() const
{
   return dependency_symbols;
}




} // namespace Cpp
} // namespace Blast


