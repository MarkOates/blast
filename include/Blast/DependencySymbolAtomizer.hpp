#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class DependencySymbolAtomizer
   {
   private:
      std::string dependency_symbol;

   public:
      DependencySymbolAtomizer(std::string dependency_symbol="");
      ~DependencySymbolAtomizer();

      void set_dependency_symbol(std::string dependency_symbol);
      std::string get_dependency_symbol() const;
      std::vector<std::string> atomize();
   };
}



