

#include <gtest/gtest.h>

#include <Blast/Action/Base.hpp>


class DerivedAction : public Blast::Action::Base
{
public:
   int counter;

   DerivedAction()
      : Blast::Action::Base("DerivedAction")
      , counter(0)
   {}
   ~DerivedAction() {}

   bool execute() override
   {
      counter++;
      return true;
   }
};


TEST(Action__BaseTest, execute__executes_the_derived_action)
{
   DerivedAction derived_action = DerivedAction();
   Blast::Action::Base *base = &derived_action;

   ASSERT_TRUE(base->execute());
   ASSERT_EQ(1, derived_action.counter);
}


TEST(Action__BaseTest, get_action_name__returns_the_name_of_the_action)
{
   DerivedAction derived_action = DerivedAction();

   ASSERT_EQ("DerivedAction", derived_action.get_action_name());
}


