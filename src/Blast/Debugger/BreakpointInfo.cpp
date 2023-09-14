

#include <Blast/Debugger/BreakpointInfo.hpp>




namespace Blast
{
namespace Debugger
{


BreakpointInfo::BreakpointInfo(std::string filename, int line)
   : filename(filename)
   , line(line)
{
}


BreakpointInfo::~BreakpointInfo()
{
}


void BreakpointInfo::set_filename(std::string filename)
{
   this->filename = filename;
}


void BreakpointInfo::set_line(int line)
{
   this->line = line;
}


std::string BreakpointInfo::get_filename() const
{
   return filename;
}


int BreakpointInfo::get_line() const
{
   return line;
}


std::string &BreakpointInfo::get_filename_ref()
{
   return filename;
}


int &BreakpointInfo::get_line_ref()
{
   return line;
}




} // namespace Debugger
} // namespace Blast


