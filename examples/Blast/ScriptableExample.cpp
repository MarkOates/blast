


#include <Blast/Scriptable.hpp>




class MyScriptableClass : public Blast::Scriptable<MyScriptableClass>
{
public:
   MyScriptableClass()
      : Scriptable()
   {
      register_function("echo", &MyScriptableClass::echo);
   }

   void echo(std::string arg)
   {
      std::cout << arg << std::endl;
   }
};



int main(int argc, char *argv[])
{
   MyScriptableClass my_scriptable_class;
   my_scriptable_class.call_function("echo", "Hello World!!");
   return 0;
}



