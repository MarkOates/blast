

#include <Blast/Cpp/GoogleTestGenerator.hpp>

#include <algorithm>
#include <cstddef>
#include <sstream>


namespace Blast
{


namespace Cpp
{


GoogleTestGenerator::GoogleTestGenerator(std::string class_name, std::string function_name, std::string description_sentence, std::string body)
   : class_name(class_name)
   , function_name(function_name)
   , description_sentence(description_sentence)
   , body(body)
{
}


GoogleTestGenerator::~GoogleTestGenerator()
{
}


std::string GoogleTestGenerator::get_description_line()
{
   std::string result = description_sentence;
   static const std::string allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";

   std::size_t pos = -1;
   while ((pos = result.find_last_not_of(allowed_chars, pos)) != std::string::npos) result[pos] = '_';
   if (!function_name.empty()) result = function_name + "__" + result;
   return result;
}


std::string GoogleTestGenerator::get_macro_opener_line()
{
   std::stringstream result;
   result << "TEST(" << class_name << "Test, " << get_description_line() << ")";
   return result.str();
}


std::string GoogleTestGenerator::get_body()
{
   return body;
}


std::string GoogleTestGenerator::render()
{
   std::stringstream result;
   result << get_macro_opener_line() << "\n{\n   " << get_body() << "\n}\n";
   return result.str();
}


} // namespace Cpp


} // namespace Blast


