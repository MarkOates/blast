

#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <Blast/RandomGenerator.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/StringPadder.hpp>

#include <iostream>
#include <sstream>


class RandomJokeGenerator
{
private:
   RandomGenerator random_generator;
   std::vector<std::string> joke_bank;

public:
   RandomJokeGenerator()
      : random_generator()
      , joke_bank()
   {}

   std::string get_joke()
   {
      fill_joke_bank();
      int index_of_choice = random_generator.get_random_int(0, joke_bank.size()-1);
      return joke_bank[index_of_choice];
   }

private:

   void fill_joke_bank()
   {
      if (!joke_bank.empty()) return;

      joke_bank = {
         "Mother asked, \"Anton, do you think I'm a bad mother?\".  Her son replied, \"My name is Paul\".",
         "My dog used to chase people on a bike a lot.  It got so bad, finally I had to take his bike away.",
         "Can a kangaroo jump higher than a house?  Of course, a hose doens't jump at all.",
         "Why did the phyiscs teacher break up with the biology teacher?  There was no chemistry.",
         "What do you name a bear without an ear?  Answer: B",
         "Does your dog bite?  Nope.  Oh, so how do you feed him?",
         "How many times did Noah go fishing?  Only twice.  He only had 2 worms.",
         "Whenever I undress in the bathroom, my shower gets turned on.",
         "A guy was admitted to a hospital with 8 plastic horses in his stomach.  His condition is now stable.",
      };
   }
};


class ExampleParser
{
private:
   Blast::CommandLineFlaggedArgumentsParser parser;

   const std::string description = "An example program showing how to use blast components and create a CLI (command line interface) " \
     "for any application";
   const std::pair<std::string, std::string> HELLO_FLAG =    { "-h", "Program will say \"Hello!\"." };
   const std::pair<std::string, std::string> HELLO_TO_FLAG = { "-H", "Program will say \"Hello [names]\"." };
   const std::pair<std::string, std::string> JOKE_FLAG =     { "-j", "Program will output a random joke." };
   const std::pair<std::string, std::string> HELP_FLAG =     { "--help", "Program will output help info (you're here now)." };
   const std::vector<std::pair<std::string, std::string>> flags = {
      HELLO_FLAG,
      HELLO_TO_FLAG,
      JOKE_FLAG,
      HELP_FLAG,
   };

public:
   ExampleParser(std::vector<std::string> args)
      : parser(args)
   {}

   ~ExampleParser() {}

   bool has_hello_flag() { return parser.has_flag(HELLO_FLAG.first); }
   bool has_hello_to_flag() { return parser.has_flag(HELLO_TO_FLAG.first); }
   bool has_joke_flag() { return parser.has_flag(JOKE_FLAG.first); }
   bool has_help_flag() { return parser.has_flag(HELP_FLAG.first); }

   std::vector<std::vector<std::string>> get_hello_to_flag_args() { return parser.get_flagged_args(HELLO_TO_FLAG.first); }

   std::string get_help()
   {
      std::stringstream result;
      result << std::endl << std::endl;
      result << "=== CommandLineFlaggedArgumentsParser ===" << std::endl;
      result << std::endl << std::endl;
      result << "Description:" << std::endl;
      result << std::endl;
      result << ExampleParser::description << std::endl;
      result << std::endl << std::endl;
      result << "Options:" << std::endl;
      result << std::endl;
      for (auto &flag : flags) {
         std::string colored_output = Blast::StringPadder(flag.first, 8, ' ').pad();
         result << "  " << "\033[1m\033[32m" << colored_output << "\033[0m" << flag.second << std::endl;
      }

      result << std::endl << std::endl;
      return result.str();
   }
};


class Controller
{
private:
   ExampleParser &parser;
   RandomJokeGenerator random_joke_generator;

public:
   Controller(ExampleParser &parser)
      : parser(parser)
      , random_joke_generator()
   {}

   ~Controller() {}

   void run()
   {
      if (parser.has_help_flag()) std::cout << parser.get_help();
      else if (parser.has_joke_flag()) std::cout << random_joke_generator.get_joke() << std::endl;
      else if (parser.has_hello_flag()) std::cout << "Hello!" << std::endl;
      else if (parser.has_hello_to_flag())
      {
         std::vector<std::vector<std::string>> name_sets = parser.get_hello_to_flag_args();
         for (auto &name_set : name_sets)
         {
            std::cout << "Hello " << Blast::StringJoiner(name_set, ", ").join() << '.' << std::endl;
         }
      }
   }
};


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   ExampleParser example_parser(args);

   Controller(example_parser).run();

   return 0;
}


