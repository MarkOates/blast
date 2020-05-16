

#include <Blast/SimpleTextSearcher.hpp>



namespace Blast
{


SimpleTextSearcher::SimpleTextSearcher(std::string search_text, std::vector<std::string> elements)
   : search_text(search_text)
   , elements(elements)
{
}


SimpleTextSearcher::~SimpleTextSearcher()
{
}


std::vector<std::string> SimpleTextSearcher::results()
{
if (search_text.empty()) return {};
return {"Hello, ", "World!"};

}
} // namespace Blast


