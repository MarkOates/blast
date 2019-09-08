

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <cstdio>
#include <string>
#include <array>
#include <memory>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <cstdio>
#include <stdexcept>


namespace Blast
{


ShellCommandExecutorWithCallback::ShellCommandExecutorWithCallback()
   : command("echo hello!")
   , callback({})
{
}


ShellCommandExecutorWithCallback::~ShellCommandExecutorWithCallback()
{
}


std::string ShellCommandExecutorWithCallback::execute()
{
static const int BUFFER_SIZE = 128;

std::array<char, BUFFER_SIZE> buffer;
std::string result;
std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

if (!pipe) throw std::runtime_error("ShellCommandExecutor::execute(): Error: popen() failed.");

while (!feof(pipe.get()))
   if (fgets(buffer.data(), BUFFER_SIZE, pipe.get()) != nullptr)
   {
      result += buffer.data();
      callback(buffer.data());
   }

return result;

}
} // namespace Blast


