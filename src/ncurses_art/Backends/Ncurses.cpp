

#include <ncurses_art/Backends/Ncurses.hpp>




namespace ncurses_art
{
namespace Backends
{


Ncurses::Ncurses(std::string property)
   : ncurses_art::Backends::Base(ncurses_art::Backends::Ncurses::TYPE)
   , property(property)
{
}


Ncurses::~Ncurses()
{
}


std::string Ncurses::get_property() const
{
   return property;
}


bool Ncurses::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}


} // namespace Backends
} // namespace ncurses_art


