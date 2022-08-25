

#include <Blast/Cpp/Function.hpp>



namespace Blast
{
namespace Cpp
{


Function::Function(std::string type, std::string name, std::vector<Blast::Cpp::FunctionArgument> signature, std::string body, bool is_static, bool is_const, bool is_override, bool is_virtual, bool is_pure_virtual, bool is_final_override, bool is_private, bool is_protected)
   : type(type)
   , name(name)
   , signature(signature)
   , body(body)
   , is_static(is_static)
   , is_const(is_const)
   , is_override(is_override)
   , is_virtual(is_virtual)
   , is_pure_virtual(is_pure_virtual)
   , is_final_override(is_final_override)
   , is_private(is_private)
   , is_protected(is_protected)
{
}


Function::~Function()
{
}


std::string Function::get_type() const
{
   return type;
}


std::string Function::get_name() const
{
   return name;
}


std::vector<Blast::Cpp::FunctionArgument> Function::get_signature() const
{
   return signature;
}


std::string Function::get_body() const
{
   return body;
}


bool Function::get_is_static() const
{
   return is_static;
}


bool Function::get_is_const() const
{
   return is_const;
}


bool Function::get_is_override() const
{
   return is_override;
}


bool Function::get_is_virtual() const
{
   return is_virtual;
}


bool Function::get_is_pure_virtual() const
{
   return is_pure_virtual;
}


bool Function::get_is_final_override() const
{
   return is_final_override;
}


bool Function::get_is_private() const
{
   return is_private;
}


bool Function::get_is_protected() const
{
   return is_protected;
}


} // namespace Cpp
} // namespace Blast


