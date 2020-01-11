

#include <Blast/Build/Celebrator.hpp>
#include <sstream>
#include <string>
#include <iomanip>
#include <iomanip>


namespace Blast
{
namespace Build
{


Celebrator::Celebrator()
{
}


Celebrator::~Celebrator()
{
}


std::string Celebrator::generate_output_banner(int width)
{
std::string value = "Hello World!";

std::stringstream stream;
stream << std::setfill('0') << std::setw(2) << value;
return stream.str();

}
} // namespace Build
} // namespace Blast


