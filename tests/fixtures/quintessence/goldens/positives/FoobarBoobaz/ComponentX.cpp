

#include <FoobarBoobaz/ComponentX.hpp>




namespace FoobarBoobaz
{


ComponentX::ComponentX()
   : my_value(42)
{
}


ComponentX::~ComponentX()
{
}


int ComponentX::get_my_value() const
{
   return my_value;
}




} // namespace FoobarBoobaz


