

#include <gtest/gtest.h>

#include <Blast/Testing/ErrorAssertions.hpp>

#include <Blast/Cpp/Class.hpp>

#include <cmath>



TEST(ClassTest, can_be_created)
{
   Blast::Cpp::Class klass;
}


TEST(ClassTest, infer_has_virtual_functions__returns_true_if_virtual_or_pure_virtual_functions_exist_in_the_class)
{
   Blast::Cpp::Class cpp_class_with_virtual_function("User", { "ProjectName" }, {}, {}, {}, {}, {
      Blast::Cpp::Function("void", "unnamed_function",         {}, "return;", false, false, false, true, false),
      Blast::Cpp::Function("void", "another_unnamed_function", {}, "return;", false, false, false, false, false),
   });

   Blast::Cpp::Class cpp_class_with_pure_virtual_function("User", { "ProjectName" }, {}, {}, {}, {}, {
      Blast::Cpp::Function("void", "unnamed_function",         {}, "return;", false, false, false, false, false),
      Blast::Cpp::Function("void", "another_unnamed_function", {}, "return;", false, false, false, false, true),
   });

   ASSERT_TRUE(cpp_class_with_virtual_function.infer_has_virtual_functions());
   ASSERT_TRUE(cpp_class_with_pure_virtual_function.infer_has_virtual_functions());
}


TEST(ClassTest,
   infer_has_virtual_functions__returns_false_if_virtual_or_pure_virtual_functions_do_not_exist_in_the_class)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {}, {});

   ASSERT_FALSE(cpp_class.infer_has_virtual_functions());
}


TEST(ClassTest,
   infer_has_constexpr_properties__returns_true_if_there_are_attributes_in_the_class_that_have_a_constexpr_qualifier)
{
   Blast::Cpp::Class cpp_class_with_constexpr_properties("User", { "ProjectName" }, {}, {
      Blast::Cpp::ClassAttributes("float", "PI", "3.141592f", true, false, false, false, false, false, false, true, false),
   });

   EXPECT_TRUE(cpp_class_with_constexpr_properties.infer_has_constexpr_properties());
}


TEST(ClassTest,
   infer_has_constexpr_properties__returns_false_if_there_are_no_constexpr_members_in_the_class)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {});

   EXPECT_FALSE(cpp_class.infer_has_constexpr_properties());
}


