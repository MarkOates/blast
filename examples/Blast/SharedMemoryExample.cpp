#ifdef BLAST_BUILD_WITH_BOOST


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



#else   // #ifdef BLAST_BUILD_WITH_BOOST


#include <iostream>
#include <sstream>


int main(int argv, char **argc)
{
   std::stringstream error_message;
   error_message << "This component requies linking with boost.  The flag BLAST_BUILD_WITH_BOOST was set to false during compilation, and the component and this example program have not been compiled.  Instead, this binary outputs this simple error message.";
   std::cout << error_message.str() << std::endl;

   return 1;
}


#endif   // #ifdef BLAST_BUILD_WITH_BOOST
