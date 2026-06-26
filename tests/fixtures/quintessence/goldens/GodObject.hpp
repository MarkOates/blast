#pragma once


#include <BaseClass.hpp>
#include <cstdint>
#include <string>


namespace quintessences
{
   class GodObject : public BaseClass
   {
   public:
      static constexpr const char* my_static_constexpr = "my_constant";

   private:
      enum class Status : int32_t
      {
         ACTIVE = 1,
         INACTIVE,
         PENDING,
      };
      enum flags
      {
         FLAG_A = 0x0001,
         FLAG_B = 0x0002,
         FLAG_C = 0x0004,
      };
      int my_int;

   protected:


   public:
      std::string my_exposed_string;
      GodObject(int my_int=42);
      ~GodObject();

      void set_my_int(int my_int);
      int get_my_int() const;
      static std::string get_status_string(Status value=Status::ACTIVE, bool throw_on_error=true);
      static Status status_from_string(std::string value="[unset-value]", bool throw_on_error=true);
      void perform_action(int value=0);
      std::string& get_exposed_string_ref() const;
   };
}



