

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


void ProgramRunner::execute_command(std::string command)
{
Blast::ShellCommandExecutorWithCallback shell_command_executor(
   command,
   Blast::ShellCommandExecutorWithCallback::simple_cout_callback
);
shell_command_executor.execute();

}

void ProgramRunner::run()
{
//  "--tag focus"
//std::string RUBY_DEV_COMMAND_RERUN = "COMPONENT_NAME=[[COMPONENT_NAME]]; rerun -c "bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb"; unset COMPONENT_NAME";
//std::string RUBY_DEV_COMMAND = "COMPONENT_NAME=[[COMPONENT_NAME]]; bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb; unset COMPONENT_NAME";

//std::string user_input;

//std::cout << "Ruby/Rspec mode" << std::endl;
//std::cout << "Type the name of the component: ";
//getline(std::cin, user_input);
//user_input = "graphql/graph_api/partners/mutations/external_job_review_create";
//std::cout << "Skipping component input. Using "" << user_input << """;
//std::cout << std::endl;

//if (user_input == "exit") break;

//std::string user_command = RUBY_DEV_COMMAND_RERUN;
//user_command = __replace(user_command, "[[COMPONENT_NAME]]", user_input);

std::vector<std::string> command_tokens;
command_tokens = {
   "echo Hello, Mark",
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


