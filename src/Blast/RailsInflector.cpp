

#include <Blast/RailsInflector.hpp>

#include <Blast/ShellCommandExecutor.hpp>
#include <algorithm>
#include <sstream>
#include <vector>


static const std::string rails_inflector_ruby_source = R"END(
begin
  require 'active_support'
rescue LoadError
  print 'error: Could not load dependency "active_support"; Rails must be installed in your local system to use this feature.' and abort
end

print 'error: Must pass "singularize" or "pluralize" as the first argument and a string as the second argument' and abort if ARGV.count != 2

print 'error: Must pass "singularize" or "pluralize" as the first argument' and abort unless %w(pluralize singularize).include?(ARGV[0])

case ARGV[0]
when 'singularize'
  print ActiveSupport::Inflector.singularize(ARGV[1])
when 'pluralize'
  print ActiveSupport::Inflector.pluralize(ARGV[1])
end
)END";


static std::string ___replace_in_string(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }

   return str;
}


static std::string ___sanitize(std::string str)
{
   str = ___replace_in_string(str, "\\", "\\\\");
   str = ___replace_in_string(str, "\"", "\\\"");

   return str;
}


namespace Blast
{


RailsInflector::RailsInflector(std::string term, inflection_operation_t inflection_operation)
   : term(term)
   , inflection_operation(inflection_operation)
{
   if (term.empty()) throw std::runtime_error("RailsInflector::RailsInflector(): term cannot be blank");
}


RailsInflector::~RailsInflector()
{
}


std::string RailsInflector::inflect()
{
   std::string compressed_single_line_ruby_source = rails_inflector_ruby_source;
   std::replace(compressed_single_line_ruby_source.begin(), compressed_single_line_ruby_source.end(), '\n', ';');

   std::string inflection_command = inflection_operation == PLURALIZE ? "pluralize" : "singularize";

   std::stringstream command;

   command << std::string("ruby -e \"")
      << ___sanitize(compressed_single_line_ruby_source)
      << "\" "
      << inflection_command
      << " \""
      << ___sanitize(term)
      << "\"";

   ShellCommandExecutor shell_command_executor(command.str());
   std::string output = shell_command_executor.execute();

   if (output.substr(0, 6) == "error:")
   {
      std::string returned_error_message = output.substr(7, -1);
      std::stringstream error_message;
      error_message
         << "There was an error when retrieving the inflection.  The following message was returned: \""
         << returned_error_message
         << "\"";

      throw std::runtime_error(error_message.str());
   }

   return output;
}


} // namespace Blast



