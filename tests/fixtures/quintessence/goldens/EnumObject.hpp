#pragma once


#include <cstdint>
#include <string>


namespace quintessences
{
   class EnumObject
   {
   public:

      enum class ConversionsEnum
      {
         STATE_INIT = 0,
         STATE_RUNNING,
         STATE_STOPPED,
      };
   protected:

      enum class CustomConversionsEnum
      {
         FOO_ONE = 0,
         FOO_TWO,
      };
   private:
      enum BasicEnum
      {
         VALUE_X = 0,
         VALUE_Y,
      };
      enum class ClassEnum : int16_t
      {
         VAL_A = 10,
         VAL_B,
         VAL_C,
      };
      enum BitwiseFlags
      {
         FLAG_X = 0x0002,
         FLAG_Y = 0x0004,
         FLAG_Z = 0x0008,
      };

   protected:


   public:
      EnumObject();
      ~EnumObject();

      static std::string to_string(ConversionsEnum value=ConversionsEnum::STATE_INIT, bool throw_on_error=true);
      static std::string name_of_foo(CustomConversionsEnum value=CustomConversionsEnum::FOO_ONE, bool throw_on_error=true);
      static ConversionsEnum from_string(std::string value="[unset-value]", bool throw_on_error=true);
      static CustomConversionsEnum foo_from_name(std::string value="[unset-value]", bool throw_on_error=true);
   };
}



