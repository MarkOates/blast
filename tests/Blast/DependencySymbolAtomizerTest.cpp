
#include <gtest/gtest.h>

#include <Blast/DependencySymbolAtomizer.hpp>


TEST(Blast_DependencySymbolAtomizerTest, can_be_created_without_blowing_up)
{
   Blast::DependencySymbolAtomizer dependency_symbol_atomizer;
}


TEST(Blast_DependencySymbolAtomizerTest, atomize__will_split_composite_dependency_into_discreet_dependencies)
{
   std::vector<std::pair<std::string, std::vector<std::string>>> test_composite_dependencies_and_their_atoms = {
     { "std::vector<std::string>", { "vector", "string" } },
   };

   for (auto &test_data : test_composite_dependencies_and_their_atoms)
   {
      std::string composite_dependency = std::get<0>(test_data);
      std::vector<std::string> expected_dependency_atoms = std::get<1>(test_data);

      Blast::DependencySymbolAtomizer dependency_symbol_atomizer(composite_dependency);

      EXPECT_EQ(expected_dependency_atoms, dependency_symbol_atomizer.atomize());
   }
}


