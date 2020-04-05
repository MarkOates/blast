

#include <Blast/Daemus/ProgramRunner.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <vector>
#include <string>
#include <sstream>


namespace Blast
{
namespace Daemus
{


ProgramRunner::ProgramRunner()
{
}


ProgramRunner::~ProgramRunner()
{
}


std::string ProgramRunner::__replace(std::string str, std::string from, std::string to)
{
size_t start_pos = 0;
while((start_pos = str.find(from, start_pos)) != std::string::npos) {
   str.replace(start_pos, from.length(), to);
   start_pos += to.length();
}
return str;

}

void ProgramRunner::execute_command(std::string command)
{
Blast::ShellCommandExecutorWithCallback shell_command_executor(
   command,
   Blast::ShellCommandExecutorWithCallback::simple_cout_callback
   //Blast::ShellCommandExecutorWithCallback::simple_silent_callback
);
shell_command_executor.execute();

}

void ProgramRunner::run()
{
std::string rerun_command = "rerun --quiet -c -p \"**/*.{" \
   "rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}" \
   "\"";
std::vector<std::string> command_tokens;
command_tokens = {
  "(cd /Users/markoates/Repos/blast/ && ",
  rerun_command,
  " make focus)",
};

std::stringstream command;
for (auto &command_token : command_tokens)
{
   command << command_token << " ";
}

execute_command(command.str());
return;

}
} // namespace Daemus
} // namespace Blast


