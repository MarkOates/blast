

#include <quintessences/EnumObject.hpp>




namespace quintessences
{


EnumObject::EnumObject()
{
}


EnumObject::~EnumObject()
{
}


std::string EnumObject::to_string(ConversionsEnum value, bool throw_on_error)
{
   if (value == ConversionsEnum::STATE_INIT) return "state_init";
   if (value == ConversionsEnum::STATE_RUNNING) return "state_running";
   if (value == ConversionsEnum::STATE_STOPPED) return "state_stopped";
   // TODO: Implement "throw_on_error" argument
   return "";
}


std::string EnumObject::name_of_foo(CustomConversionsEnum value, bool throw_on_error)
{
   if (value == CustomConversionsEnum::FOO_ONE) return "one";
   if (value == CustomConversionsEnum::FOO_TWO) return "two";
   // TODO: Implement "throw_on_error" argument
   return "";
}


EnumObject::ConversionsEnum EnumObject::from_string(std::string value, bool throw_on_error)
{
   if (value == "state_init") return ConversionsEnum::STATE_INIT;
   if (value == "state_running") return ConversionsEnum::STATE_RUNNING;
   if (value == "state_stopped") return ConversionsEnum::STATE_STOPPED;
   throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for \" + value + \"");
}


EnumObject::CustomConversionsEnum EnumObject::foo_from_name(std::string value, bool throw_on_error)
{
   if (value == "one") return CustomConversionsEnum::FOO_ONE;
   if (value == "two") return CustomConversionsEnum::FOO_TWO;
   throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for \" + value + \"");
}




} // namespace quintessences


