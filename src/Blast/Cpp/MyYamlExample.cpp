

#include <Blast/Cpp/MyYamlExample.hpp>



namespace Blast
{
namespace Cpp
{


MyYamlExample::MyYamlExample(std::string person_name)
   : person_name(person_name)
{
}


MyYamlExample::~MyYamlExample()
{
}


void MyYamlExample::set_person_name(std::string person_name)
{
   this->person_name = person_name;
}


std::string MyYamlExample::get_person_name()
{
   return person_name;
}


std::string MyYamlExample::my_function(std::string person_name)
{
return std::string("Hello, ") + person_name + "!";

}
} // namespace Cpp
} // namespace Blast


