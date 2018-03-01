

#include <Blast/CppSelectorPatternGenerator.hpp>


int main(int, char**)
{
   Blast::CppSelectorPatternGenerator generator("Staff", "trombones", "element->attributes.matches(\"type\", \"trombone\")", "Staff::Instrument");

   std::cout << "-----------------------------------" << std::endl;
   std::cout << generator.render_declaration() << std::endl;

   std::cout << "-----------------------------------" << std::endl;
   std::cout << generator.render_definition() << std::endl;

   return 0;
}


