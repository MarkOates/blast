#include <allegro5/allegro.h>


#include <string>   // std::string
#include <iostream> // std::cout
#include <sstream>  // std::stringstream

int main(int argc, char** argv)
{
   std::string expected = "This is a test that prints to stdout";

   std::stringstream buffer;
   // Redirect std::cout to buffer
   std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

   // BEGIN: Code being tested
   std::cout << "This is a test that prints to stdout" << std::endl;
   // END:   Code being tested

   // Use the string value of buffer to compare against expected output
   std::string text = buffer.str();
   int result = text.compare(expected);

   // Restore original buffer before exiting
   std::cout.rdbuf(prevcoutbuf);

   if (!result) {
      std::cout << "Failed" << std::endl;
      std::exit(1);
   }
   std::cout << "Success" << std::endl;
   std::exit(0);
}


