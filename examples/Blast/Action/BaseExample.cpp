

#include <Blast/Action/Base.hpp>
#include <iostream>


class ProgramState
{
private:
   bool program_is_aborted;
   int counter;

public:
   ProgramState()
      : program_is_aborted(false)
      , counter(0)
   {}
   void increment_counter()
   {
      counter++;
   }
   int get_counter()
   {
      return counter;
   }
   void abort_program()
   {
      program_is_aborted = true;
   }
   bool is_program_aborted()
   {
      return program_is_aborted;
   }
};


class ProgramAborter : public Blast::Action::Base
{
private:
   ProgramState *program_state;

public:
   ProgramAborter(ProgramState *program_state)
      : Blast::Action::Base("ProgramAborter")
      , program_state(program_state)
   {}
   ~ProgramAborter() {}

   bool execute() override
   {
      if (!program_state)
         throw std::invalid_argument("Cannot program_state->abort_program() when program_state is nullptr.");

      std::cout << "Aborting program." << std::endl;
      program_state->abort_program();
      return true;
   }
};


class ProgramCounterIncrementer : public Blast::Action::Base
{
private:
   ProgramState *program_state;

public:
   ProgramCounterIncrementer(ProgramState *program_state)
      : Blast::Action::Base("ProgramCounterIncrementer")
      , program_state(program_state)
   {}
   ~ProgramCounterIncrementer() {}

   bool execute() override
   {
      if (!program_state)
         throw std::invalid_argument("Cannot program_state->increment_counter() when program_state is nullptr.");

      std::cout << "Incrementing counter...";
      program_state->increment_counter();
      std::cout << " counter is now at " << program_state->get_counter() << std::endl;
      return true;
   }
};


int main(int argc, char **argv)
{
   ProgramState program_state;
   Blast::Action::Base *action = nullptr;

   while (!program_state.is_program_aborted())
   {
      if (program_state.get_counter() < 10) action = new ProgramCounterIncrementer(&program_state);
      else action = new ProgramAborter(&program_state);

      action->execute();
      delete action;
   }

   return 0;
}


