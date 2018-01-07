#include <gtest/gtest.h>


#include <Blast/Scriptable.hpp>


class MyScriptableClass : public Blast::Scriptable<MyScriptableClass>
{
private:
   std::string color;

public:
   MyScriptableClass()
      : color("blue")
   {
      register_function("set_color", &MyScriptableClass::set_color);
   }

   void set_color(std::string arg)
   {
      color = arg;
   }

   void set_color_chartreuse(std::string)
   {
      color = "chartreuse";
   }

   std::string get_color()
   {
      return color;
   }
};


TEST(ScriptableTest, derived_class_can_be_created)
{
   MyScriptableClass my_scriptable_class;
}


TEST(ScriptableTest, can_call_registered_functions)
{
   MyScriptableClass my_scriptable_class;

   my_scriptable_class.call_function("set_color", "pink");
   ASSERT_EQ("pink", my_scriptable_class.get_color());

   my_scriptable_class.call_function("set_color", "blue");
   ASSERT_EQ("blue", my_scriptable_class.get_color());
}


TEST(ScriptableTest, can_register_a_function)
{
   MyScriptableClass my_scriptable_class;

   ASSERT_FALSE(my_scriptable_class.function_exists("set_color_chartreuse"));

   my_scriptable_class.register_function("set_color_chartreuse", &MyScriptableClass::set_color_chartreuse);

   ASSERT_TRUE(my_scriptable_class.function_exists("set_color_chartreuse"));
}


TEST(ScriptableTest, when_registering_a_function_to_an_identifier_that_already_exists_raises_an_exception)
{
   MyScriptableClass my_scriptable_class;

   ASSERT_THROW(my_scriptable_class.register_function("set_color", &MyScriptableClass::set_color_chartreuse), std::runtime_error);
}


TEST(ScriptableTest, when_calling_an_unregistered_function_raises_an_exception)
{
   MyScriptableClass my_scriptable_class;

   ASSERT_THROW(my_scriptable_class.call_function("function_that_does_not_exist", "pink"), std::runtime_error);
}


TEST(ScriptableTest, returns_true_when_a_funcion_exists)
{
   MyScriptableClass my_scriptable_class;

   ASSERT_TRUE(my_scriptable_class.function_exists("set_color"));
}


TEST(ScriptableTest, returns_false_when_a_funcion_does_not_exist)
{
   MyScriptableClass my_scriptable_class;

   ASSERT_FALSE(my_scriptable_class.function_exists("function_that_does_not_exist"));
}


