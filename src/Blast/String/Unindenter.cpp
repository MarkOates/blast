

#include <Blast/String/Unindenter.hpp>

#include <Blast/StringJoiner.hpp>
#include <Blast/StringSplitter.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace Blast
{
namespace String
{


Unindenter::Unindenter(std::string content)
   : content(content)
{
}


Unindenter::~Unindenter()
{
}


std::string Unindenter::indent(std::size_t num_indents)
{
   if (!((num_indents >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Unindenter::indent]: error: guard \"(num_indents >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Unindenter::indent: error: guard \"(num_indents >= 0)\" not met");
   }
   std::vector<std::string> lines = Blast::StringSplitter(content, '\n').split();
   bool skip_blank_lines = true;

   std::string prefix_string(num_indents, ' ');

   //int min_num_spaces = 9999;
   for (auto &line : lines)
   {
      if (skip_blank_lines && line.empty()) continue;
      line = prefix_string + line;

      //int count = 0;
      //for (char ch : line)
      //{
         //if (ch == ' ') count++;
         //else break;
      //}

      //if (count < min_num_spaces) min_num_spaces = count;
   }

   //if (num_indents > min_num_spaces)
   //{
      // Consider if should be reduced to left edge
   //}
   //else
   //{
      //for (auto &line : lines)
      //{
         //if (skip_blank_lines && line.empty()) continue;

         //line = line.substr(num_unindents);
      //}
   //}

   // Get the result as a string
   return Blast::StringJoiner(lines, "\n").join() + "\n";
}

std::string Unindenter::unindent(std::size_t num_unindents)
{
   if (!((num_unindents >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Unindenter::unindent]: error: guard \"(num_unindents >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Unindenter::unindent: error: guard \"(num_unindents >= 0)\" not met");
   }
   std::vector<std::string> lines = Blast::StringSplitter(content, '\n').split();
   bool skip_blank_lines = true;

   int min_num_spaces = 9999;
   for (auto &line : lines)
   {
      if (skip_blank_lines && line.empty()) continue;

      int count = 0;
      for (char ch : line)
      {
         if (ch == ' ') count++;
         else break;
      }

      if (count < min_num_spaces) min_num_spaces = count;
   }

   if (num_unindents > min_num_spaces)
   {
      // Consider if should be reduced to left edge
   }
   else
   {
      for (auto &line : lines)
      {
         if (skip_blank_lines && line.empty()) continue;

         line = line.substr(num_unindents);
      }
   }

   // Get the result as a string
   return Blast::StringJoiner(lines, "\n").join() + "\n";
}


} // namespace String
} // namespace Blast


