

#include <Blast/CppFunction.hpp>


namespace Blast
{


CppFunction::CppFunction(std::string type, std::string name, std::vector<Blast::CppFunctionArgument> signature, std::string body, bool is_static, bool is_const, bool is_override)
   : type(type)
   , name(name)
   , signature(signature)
   , body(body)
   , is_static(is_static)
   , is_const(is_const)
   , is_override(is_override)
{
}


CppFunction::~CppFunction()
{
}


std::string CppFunction::get_type()
{
   return type;
}


std::string CppFunction::get_name()
{
   return name;
}


std::vector<Blast::CppFunctionArgument> CppFunction::get_signature()
{
   return signature;
}


std::string CppFunction::get_body()
{
   return body;
}


bool CppFunction::get_is_static()
{
   return is_static;
}


bool CppFunction::get_is_const()
{
   return is_const;
}


bool CppFunction::get_is_override()
{
   return is_override;
}


} // namespace Blast


