#pragma once


#include <Blast/Cpp/FunctionArgument.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class Function
      {
      private:
         std::string type;
         std::string name;
         std::vector<Blast::Cpp::FunctionArgument> signature;
         std::string body;
         bool is_static;
         bool is_const;
         bool is_override;
         bool is_virtual;
         bool is_pure_virtual;
         bool is_final_override;
         bool is_private;
         bool is_protected;

      protected:


      public:
         Function(std::string type="void", std::string name="unnamed_function", std::vector<Blast::Cpp::FunctionArgument> signature={}, std::string body="return;", bool is_static=false, bool is_const=false, bool is_override=false, bool is_virtual=false, bool is_pure_virtual=false, bool is_final_override=false, bool is_private=false, bool is_protected=false);
         ~Function();

         void set_type(std::string type);
         void set_name(std::string name);
         std::string get_type() const;
         std::string get_name() const;
         std::vector<Blast::Cpp::FunctionArgument> get_signature() const;
         std::string get_body() const;
         bool get_is_static() const;
         bool get_is_const() const;
         bool get_is_override() const;
         bool get_is_virtual() const;
         bool get_is_pure_virtual() const;
         bool get_is_final_override() const;
         bool get_is_private() const;
         bool get_is_protected() const;
      };
   }
}



