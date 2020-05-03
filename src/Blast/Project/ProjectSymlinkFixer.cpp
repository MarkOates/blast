

#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <fstream>


namespace Blast
{
namespace Project
{


ProjectSymlinkFixer::ProjectSymlinkFixer()
{
}


ProjectSymlinkFixer::~ProjectSymlinkFixer()
{
}


bool ProjectSymlinkFixer::starts_with(std::string source, std::string string_to_find)
{
return source.rfind(string_to_find, 0) == 0;

}

int ProjectSymlinkFixer::line_count(std::string filename)
{
std::ifstream myfile(filename);

// new lines will be skipped unless we stop it from happening:
myfile.unsetf(std::ios_base::skipws);

// count the newlines with an algorithm specialized for counting:
unsigned line_count = std::count(
      std::istream_iterator<char>(myfile),
      std::istream_iterator<char>(),
      '\n');

//std::cout << "Lines: " << line_count << "\n";}
return line_count;

}

std::string ProjectSymlinkFixer::read_file_firstline(std::string filename)
{
std::ifstream infile(filename);

std::string sLine;
if (infile.good())
{
   getline(infile, sLine);
}
else
{
   throw std::runtime_error("Unexpected error in read_file_firstline");
}

infile.close();

return sLine;

}

bool ProjectSymlinkFixer::likely_an_intended_symlink(std::string filename, std::string string_to_find)
{
std::ifstream infile(filename);
bool starts_with_string = false;

if (infile.good())
{
   std::string sLine;
   getline(infile, sLine);
   //std::cout << sLine << std::endl;
   if (starts_with(sLine, string_to_find)) starts_with_string = true;
   if (starts_with(sLine, "../") && line_count(filename) == 1) starts_with_string = true;
}

infile.close();

return starts_with_string;

}

std::string ProjectSymlinkFixer::run()
{
return "Hello World!";
}
} // namespace Project
} // namespace Blast


