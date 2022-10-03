

#include <Blast/DependencySymbolAtomizer.hpp>

#include <Blast/StringSplitter.hpp>
#include <algorithm>


namespace Blast
{


DependencySymbolAtomizer::DependencySymbolAtomizer(std::string dependency_symbol)
   : dependency_symbol(dependency_symbol)
{
}


DependencySymbolAtomizer::~DependencySymbolAtomizer()
{
}


void DependencySymbolAtomizer::set_dependency_symbol(std::string dependency_symbol)
{
   this->dependency_symbol = dependency_symbol;
}


std::string DependencySymbolAtomizer::get_dependency_symbol() const
{
   return dependency_symbol;
}


std::vector<std::string> DependencySymbolAtomizer::atomize()
{
   std::string possibly_composite_dep = dependency_symbol;
   std::vector<char> chars_to_replace = { ',', '>', '<', '&', '*', '(', ')' };

   // replace the chars
   for (auto &char_to_replace : chars_to_replace)
   {
      std::replace(possibly_composite_dep.begin(), possibly_composite_dep.end(), char_to_replace, ' ');
   }

   // split it into tokens
   std::vector<std::string> tokenized_deps = Blast::StringSplitter(possibly_composite_dep, ' ').split();

   // create list of aomized tokens that should be discarded
   std::vector<std::string> items_to_discard = { "const", "unsigned" };

   // erase the empty tokens, and/or discard unwanted tokens
   for (int i=0; i<tokenized_deps.size(); i++)
   {
      if (tokenized_deps[i].empty())
      {
         tokenized_deps.erase(tokenized_deps.begin()+i);
         i--;
      }

      for (auto &item_to_discard : items_to_discard)
      {
         if (tokenized_deps[i] == item_to_discard)
         {
            tokenized_deps.erase(tokenized_deps.begin()+i);
            i--;
         }
      }
   }

   return tokenized_deps;
}


} // namespace Blast


