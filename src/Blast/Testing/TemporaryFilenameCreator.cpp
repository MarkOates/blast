

#include <Blast/Testing/TemporaryFilenameCreator.hpp>




namespace Blast
{
namespace Testing
{


TemporaryFilenameCreator::TemporaryFilenameCreator()
{
}


TemporaryFilenameCreator::~TemporaryFilenameCreator()
{
}


std::string TemporaryFilenameCreator::create()
{
   return std::tmpnam(nullptr);
}


} // namespace Testing
} // namespace Blast


