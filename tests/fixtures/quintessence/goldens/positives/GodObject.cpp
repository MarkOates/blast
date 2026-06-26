

#include <GodObject.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>




GodObject::GodObject(int my_int)
   : BaseClass("base_constructor_arg")
   , my_int(my_int)
   , my_exposed_string("hello")
{
}


GodObject::~GodObject()
{
}


void GodObject::set_my_int(int my_int)
{
   this->my_int = my_int;
}


int GodObject::get_my_int() const
{
   return my_int;
}


std::string GodObject::get_status_string(Status value, bool throw_on_error)
{
   if (value == Status::ACTIVE) return "active";
   if (value == Status::INACTIVE) return "inactive";
   if (value == Status::PENDING) return "pending";
   // TODO: Implement "throw_on_error" argument
   return "";
}


GodObject::Status GodObject::status_from_string(std::string value, bool throw_on_error)
{
   if (value == "active") return Status::ACTIVE;
   if (value == "inactive") return Status::INACTIVE;
   if (value == "pending") return Status::PENDING;
   throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for \" + value + \"");
}


void GodObject::perform_action(int value)
{
   if (!(value >= 0))
   {
      std::stringstream error_message;
      error_message << "[GodObject::perform_action]: error: guard \"value >= 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[GodObject::perform_action]: error: guard \"value >= 0\" not met");
   }
   // perform action here
   return;
}

std::string& GodObject::get_exposed_string_ref() const
{
   return my_exposed_string;
}




