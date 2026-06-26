

#include <Foo/Bar/Baz/ComponentY.hpp>




namespace Foo
{
namespace Bar
{
namespace Baz
{


ComponentY::ComponentY()
   : my_value(42)
{
}


ComponentY::~ComponentY()
{
}


int ComponentY::get_my_value() const
{
   return my_value;
}




} // namespace Baz
} // namespace Bar
} // namespace Foo


