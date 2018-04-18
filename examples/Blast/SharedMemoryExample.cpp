

#include <Blast/SharedMemory.hpp>
#include <iostream>
#include <string>


using namespace Blast;


int main(int argv, char **argc)
{
   if (argv <= 1)
   {
      std::cout << "You must pass \"sender\" or \"receiver\" as an to run as sender or receiver mode" << std::endl;
   }
   else if (strncmp(argc[1], "sender", 6) == 0)
   {
      std::cout << "Running in \"sender\" mode" << std::endl;
      std::cout << "Type your message: " << std::flush;

      SharedMemory shared_memory("shared_message_memory", 256);

      std::string input;
      std::cin >> input;

      shared_memory.write(input);

      std::cout << "Message written." << std::endl;
   }
   else if (strncmp(argc[1], "receiver", 8) == 0)
   {
      std::cout << "Running in \"receiver\" mode" << std::endl;
      std::cout << "Waiting for message" << std::flush;

      SharedMemory shared_memory("shared_message_memory", 256);
      while (shared_memory.is_empty())
      {
         std::cout << '.' << std::flush;
         sleep(2);
      }

      std::cout << "message received: \"" << shared_memory.read() << "\"" << std::endl;
   }

   return 0;
}


