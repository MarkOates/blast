#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class CommandLineFlaggedArgumentsParser
   {
   private:
      std::vector<std::string> command_line_args;
      std::vector<int> find_flag_positions(std::string flag);
      std::vector<std::string> get_args_within_flag(int arg_position);
      bool is_flag(std::string potential_flag_value);

   public:
      // NOTE! this constructor performs logic inside of it's body. The logic could potentially
      // crash or cause side effects and guards have not been implemented.  Be sure to pass
      // verbatum the arguments that come from the program's entry, or add the necessary features
      // properly guard this function body.
      CommandLineFlaggedArgumentsParser(int argc, char **argv);
      CommandLineFlaggedArgumentsParser(std::vector<std::string> command_line_args);
      ~CommandLineFlaggedArgumentsParser();

      bool has_flag(std::string flag);
      std::vector<std::vector<std::string>> get_flagged_args(std::string flag);
   };
} // namespace Blast


