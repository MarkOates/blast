

#include <Blast/ClassAttributeProperties.hpp>

#include <iostream>


int main(int argc, char **argv)
{
   ClassAttributeProperties class_attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, true, false, false);

   std::cout << "in declaration: " << class_attribute_properties.as_constructor_argument_in_declaration() << std::endl;
   std::cout << "in definition: " << class_attribute_properties.as_constructor_argument_in_definition() << std::endl;
   std::cout << "in initialization list: " << class_attribute_properties.as_argument_in_initialization_list() << std::endl;

   return 0;
}


