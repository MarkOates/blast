/*
```
enum_classes:
  - name: State
    include_undef_item: true (default)
    to_string_func: true (default)
    from_string_func: true (default)
    to_int_func: false (default)
    from_int_func: false (default)
    items:
      - RUNNING
      - HIDING
```
*/

#include <string>
#include <map>


class MyClass
{
public:
   enum class State
   {
      UNDEF = 0,
      RUNNING,
      HIDING,
   };

   std::string to_string(MyClass::State state, bool throw_on_error=true)
   {
      switch (state)
      {
         case State::UNDEF: return "undef"; break; // (if include_undef_item: == true)
         case State::RUNNING: return "running"; break;
         case State::HIDING: return "hiding"; break;
         default:
            if (throw_on_error)
            {
               // TODO: throw here
            };
         break;
      }
   }

   MyClass::State from_string(std::string identifier, bool throw_on_error=true)
   {
      static const std::map<std::string, MyClass::State> state_names = {
         { "undef", State::UNDEF }, // (if include_undef_item == true)
         { "running", State::RUNNING },
         { "hiding", State::HIDING},
      };

      if (state_names.count(identifier) == 0)
      {
         if (throw_on_error)
         {
            // TODO: throw here
         }
         else
         {
            // TODO: resolve what to do in this case
         }
      }

      return state_names.at(identifier);
   }
};


int main(int argc, char** argv)
{
   return 0;
}


