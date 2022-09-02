

#include <ncurses_art/Backends/Base.hpp>




namespace ncurses_art
{
namespace Backends
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Backends
} // namespace ncurses_art


