

#include <Blast/Cpp/SelectorPatternGenerator.hpp>


static void __replace(std::string &str, const std::string &find_str, const std::string &replace_str)
{
  std::string::size_type pos = 0u;

  while((pos = str.find(find_str, pos)) != std::string::npos)
  {
     str.replace(pos, find_str.length(), replace_str);
     pos += replace_str.length();
  }
}


static std::string function_template_declaration = R"END(std::vector<[[CLASS_NAME]] *> [[FUNCTION_NAME]]();)END";

static std::string function_template_definition = R"END(std::vector<[[CLASS_NAME]] *> [[CLASS_NAME]]Selector::[[FUNCTION_NAME]]()
{
   if (!pool) throw std::runtime_error("[[[CLASS_NAME]]Selector::[[FUNCTION_NAME]]() error:] cannot select on a nullptr pool.");

   std::vector<[[CLASS_NAME]] *> results;

   for (auto &element : *pool)
   {
      if ([[SELECTOR_CONDITION]]) results.push_back(element);
   }

   return results;
}
)END";


static std::string casted_function_template_declaration = R"END(std::vector<[[CASTED_TYPE]] *> [[FUNCTION_NAME]]();)END";


static std::string casted_function_template_definition = R"END(std::vector<[[CASTED_TYPE]] *> [[CLASS_NAME]]Selector::[[FUNCTION_NAME]]()
{
   if (!pool) throw std::runtime_error("[[[CLASS_NAME]]Selector::[[FUNCTION_NAME]]() error:] cannot select on a nullptr pool.");

   std::vector<[[CASTED_TYPE]] *> results;

   for (auto &element : *pool)
   {
      [[CASTED_TYPE]] *casted_element = static_cast<[[CASTED_TYPE]] *>(element);
      if ([[SELECTOR_CONDITION]]) results.push_back(casted_element);
   }

   return results;
}
)END";


namespace Blast
{


namespace Cpp
{


SelectorPatternGenerator::SelectorPatternGenerator(std::string class_name, std::string function_name, std::string selector_condition, std::string casted_type)
   : class_name(class_name)
   , function_name(function_name)
   , selector_condition(selector_condition)
   , casted_type(casted_type)
{
}


SelectorPatternGenerator::~SelectorPatternGenerator()
{
}


std::string SelectorPatternGenerator::render_declaration()
{
   std::string result = "";
   if (casted_type.empty())
   {
      result = function_template_declaration;
      __replace(result, "[[CLASS_NAME]]", class_name);
      __replace(result, "[[SELECTOR_CONDITION]]", selector_condition);
      __replace(result, "[[FUNCTION_NAME]]", function_name);
   }
   else
   {
      result = casted_function_template_declaration;
      __replace(result, "[[CLASS_NAME]]", class_name);
      __replace(result, "[[CASTED_TYPE]]", casted_type);
      __replace(result, "[[SELECTOR_CONDITION]]", selector_condition);
      __replace(result, "[[FUNCTION_NAME]]", function_name);
   }
   return result;
}


std::string SelectorPatternGenerator::render_definition()
{
   std::string result = "";
   if (casted_type.empty())
   {
      result = function_template_definition;
      __replace(result, "[[CLASS_NAME]]", class_name);
      __replace(result, "[[SELECTOR_CONDITION]]", selector_condition);
      __replace(result, "[[FUNCTION_NAME]]", function_name);
   }
   else
   {
      result = casted_function_template_definition;
      __replace(result, "[[CLASS_NAME]]", class_name);
      __replace(result, "[[CASTED_TYPE]]", casted_type);
      __replace(result, "[[SELECTOR_CONDITION]]", selector_condition);
      __replace(result, "[[FUNCTION_NAME]]", function_name);
   }
   return result;
}


} // namespace Cpp


} // namespace Blast


