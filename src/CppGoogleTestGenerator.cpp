

#include <Blast/CppGoogleTestGenerator.hpp>

#include <algorithm>
#include <cstddef>
#include <sstream>


namespace Blast
{


CppGoogleTestGenerator::CppGoogleTestGenerator(std::string class_name, std::string function_name, std::string description_sentence, std::string body)
   : class_name(class_name)
   , function_name(function_name)
   , description_sentence(description_sentence)
   , body(body)
{
}


CppGoogleTestGenerator::~CppGoogleTestGenerator()
{
}


std::string CppGoogleTestGenerator::get_description_line()
{
   std::string result = description_sentence;
   static const std::string allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";

   std::size_t pos = -1;
   while ((pos = result.find_last_not_of(allowed_chars, pos)) != std::string::npos) result[pos] = '_';
   if (!function_name.empty()) result = function_name + "__" + result;
   return result;
}


std::string CppGoogleTestGenerator::get_macro_opener_line()
{
   std::stringstream result;
   result << "TEST(" << class_name << "Test, " << get_description_line() << ")";
   return result.str();
}


std::string CppGoogleTestGenerator::get_body()
{
   return body;
}


std::string CppGoogleTestGenerator::render()
{
   std::stringstream result;
   result << get_macro_opener_line() << "\n{\n   " << get_body() << "\n}\n";
   return result.str();
}


} // namespace Blast


