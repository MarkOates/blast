

#include <gtest/gtest.h>

#include <Blast/Cpp/Class.hpp>

#include <cmath>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


///////


TEST(ClassTest, can_be_created)
{
   Blast::Cpp::Class klass;
}


TEST(ClassTest, infer_has_virtual_functions__returns_true_if_virtual_or_pure_virtual_functions_exist_in_the_class)
{
   Blast::Cpp::Class cpp_class_with_virtual_function("User", { "ProjectName" }, {}, {}, {
      Blast::Cpp::Function("void", "unnamed_function",         {}, "return;", false, false, false, true, false),
      Blast::Cpp::Function("void", "another_unnamed_function", {}, "return;", false, false, false, false, false),
   });

   Blast::Cpp::Class cpp_class_with_pure_virtual_function("User", { "ProjectName" }, {}, {}, {
      Blast::Cpp::Function("void", "unnamed_function",         {}, "return;", false, false, false, false, false),
      Blast::Cpp::Function("void", "another_unnamed_function", {}, "return;", false, false, false, false, true),
   });

   ASSERT_TRUE(cpp_class_with_virtual_function.infer_has_virtual_functions());
   ASSERT_TRUE(cpp_class_with_pure_virtual_function.infer_has_virtual_functions());
}


TEST(ClassTest, infer_has_virtual_functions__returns_false_if_virtual_or_pure_virtual_functions_do_not_exist_in_the_class)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {});

   ASSERT_FALSE(cpp_class.infer_has_virtual_functions());
}


