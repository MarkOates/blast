

#include <Blast/Cpp/ParentClassProperties.hpp>

#include <iostream>


int main(int argc, char **argv)
{
   Blast::Cpp::ParentClassProperties parent_class_properties("Animal", "\"Dog\"", "public");

   std::cout << "class name: " << parent_class_properties.get_class_name() << std::endl;
   std::cout << "scope specifier: " << parent_class_properties.get_scope_specifier() << std::endl;
   std::cout << "constructor arguments: " << parent_class_properties.get_constructor_arguments() << std::endl;

   return 0;
}


