#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class ParentClassProperties
   {
   private:
      bool __validate_scope_specifier(bool raise_on_error);

      std::string class_name;
      std::string constructor_arguments;
      std::string scope_specifier;

   public:
      ParentClassProperties(std::string class_name="", std::string constructor_arguments="", std::string scope_specifier="public");
      ~ParentClassProperties();

      void set_class_name(std::string class_name);
      void set_constructor_arguments(std::string constructor_arguments);
      void set_scope_specifier(std::string scope_specifier);

      std::string get_class_name();
      std::string get_constructor_arguments();
      std::string get_scope_specifier();
   };
}


