

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

std::string ProjectSymlinkFixer::run()
{
return "Hello World!";
}
} // namespace Project
} // namespace Blast


