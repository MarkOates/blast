

#include <Blast/Action/Queue.hpp>
#include <iostream>


class ProgramState
{
private:
   int counter;

public:
   ProgramState()
      : counter(0)
   {}
   ~ProgramState()
   {}

   void increment_counter()
   {
      counter++;
   }
   int get_counter()
   {
      return counter;
   }
};


class CounterIncrementer : public Blast::Action::Base
{
public:
   ProgramState *program_state;

   CounterIncrementer(ProgramState *program_state)
      : Blast::Action::Base("CounterIncrementer")
      , program_state(program_state)
   {}
   ~CounterIncrementer() {}

   bool execute() override
   {
      if (!program_state)
         throw std::runtime_error("Cannot increment counter on a nulptr program_state");

      std::cout << "Incrementing counter...";
      program_state->increment_counter();
      std::cout << " counter is now at " << program_state->get_counter() << std::endl;
      return true;
   }
};


int main(int argc, char **argv)
{
   ProgramState program_state;
   Blast::Action::Queue queue("Queue(CounterIncrementer)");

   for (int i=0; i<10; i++)
      queue.add_action(new CounterIncrementer(&program_state));

   std::cout << "Executing Queue..." << std::endl;
   queue.execute();
   std::cout << "... Queue execution complete." << std::endl;

   return 0;
}


