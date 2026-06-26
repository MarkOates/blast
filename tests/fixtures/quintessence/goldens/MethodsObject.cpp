

#include <quintessences/MethodsObject.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


namespace quintessences
{


MethodsObject::MethodsObject()
   : dummy_prop(0)
{
}


MethodsObject::~MethodsObject()
{
   // Custom destructor logic here
   dummy_prop = -1;
}


float MethodsObject::static_func(float factor)
{
   return factor * 2.0f;
}

std::string MethodsObject::const_func() const
{
   return "const value";
}

void MethodsObject::virtual_func()
{
   // base virtual func
}


void MethodsObject::override_func()
{
   // overridden func
}

bool MethodsObject::guarded_func(int* value, int threshold)
{
   if (!(value != nullptr))
   {
      std::stringstream error_message;
      error_message << "[quintessences::MethodsObject::guarded_func]: error: guard \"value != nullptr\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[quintessences::MethodsObject::guarded_func]: error: guard \"value != nullptr\" not met");
   }
   if (!(threshold > 0))
   {
      std::stringstream error_message;
      error_message << "[quintessences::MethodsObject::guarded_func]: error: guard \"threshold > 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[quintessences::MethodsObject::guarded_func]: error: guard \"threshold > 0\" not met");
   }
   return (*value) > threshold;
}


} // namespace quintessences


