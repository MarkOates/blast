#pragma once



#include <iostream>
#include <map>
#include <sstream>
#include <string>



namespace Blast
{



template <class T>
class Scriptable
{
private:
   typedef void (T::*scriptable_func)(std::string arg);
   std::map<std::string, scriptable_func> functions;

   scriptable_func find_function(std::string identifier)
   {
      auto it = functions.find(identifier);
      if (it == functions.end()) return nullptr;
      return (*it).second;
   }

public:
   Scriptable() : functions() {}
   ~Scriptable() {}

   void register_function(std::string identifier, scriptable_func function)
   {
      if (function_exists(identifier))
      {
         T *calling_object = (T *)(this);
         std::string class_name = typeid(calling_object).name();
         std::stringstream error_message;
         error_message << "Cannot register function \"" << identifier << "\"; It already exists for \"" << class_name << "\"" << std::endl;

         throw std::runtime_error(error_message.str());
      }

      functions[identifier] = function;
   }

   bool function_exists(std::string identifier)
   {
      return functions.find(identifier) != functions.end();
   }

   void call_function(std::string identifier, std::string args)
   {
      T *calling_object = (T *)(this);

      scriptable_func found_func = find_function(identifier);

      if (!found_func)
      {
         std::string class_name = typeid(calling_object).name();
         std::stringstream error_message;
         error_message << "Cannot call function \"" << identifier << "\"; It does not exist for " << std::endl;

         throw std::runtime_error(error_message.str());
      }
         
      (calling_object->*found_func)(args);
   }
};



}



