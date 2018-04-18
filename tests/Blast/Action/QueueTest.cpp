

#include <gtest/gtest.h>

#include <Blast/Action/Queue.hpp>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


class TestAction : public Blast::Action::Base
{
public:
   static int num_active;

   bool executed;

   TestAction()
      : Blast::Action::Base("TestAction")
      , executed(false)
   {
      num_active++;
   }
   ~TestAction()
   {
      num_active--;
   }

   bool execute() override
   {
      executed = true;
      return true;
   }
};


class ReturnsFalseAction : public Blast::Action::Base
{
public:
   ReturnsFalseAction() : Blast::Action::Base("ReturnsFalseAction") {}
   ~ReturnsFalseAction() {}
   bool execute() override { return false; }
};


class ThrowsExceptionAction : public Blast::Action::Base
{
public:
   ThrowsExceptionAction() : Blast::Action::Base("ThrowsExceptionAction") {}
   ~ThrowsExceptionAction() {}
   bool execute() override { throw std::runtime_error("ThrowsExceptionAction: Exception Thrown"); return false; }
};


int TestAction::num_active = 0;


TEST(Action__BaseTest, get_action_name__returns_the_name_of_the_action)
{
   Blast::Action::Queue action_queue("MyQueue");

   ASSERT_EQ("Queue<MyQueue>", action_queue.get_action_name());
}


TEST(Action__BaseTest, get_actions__returns_the_actions_in_the_queue)
{
   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction(), new TestAction() };
   Blast::Action::Queue action_queue("MyQueue", actions);

   ASSERT_EQ(actions, action_queue.get_actions());
}


TEST(Action__BaseTest, assigns_actions_when_they_are_passed_as_a_constructor_argument)
{
   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction(), new TestAction() };
   Blast::Action::Queue action_queue("MyQueue", actions);

   ASSERT_EQ(actions, action_queue.get_actions());
}


TEST(Action__BaseTest, add_action__appends_the_action_to_the_queue)
{
   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction() };
   Blast::Action::Queue action_queue("MyQueue", actions);
   TestAction *action_to_append = new TestAction();

   ASSERT_TRUE(action_queue.add_action(action_to_append));

   std::vector<Blast::Action::Base *> returned_actions = action_queue.get_actions();
   ASSERT_FALSE(returned_actions.empty());
   ASSERT_EQ(action_to_append, returned_actions.back());
}


TEST(Action__BaseTest, execute__throws_an_exception_when_an_executed_queued_action_returns_false)
{
   Blast::Action::Queue action_queue("MyQueue", { new ReturnsFalseAction() });

   std::string expected_message = "Queue<MyQueue> error: The queued action \"ReturnsFalseAction\" returned false when executed.";
   ASSERT_THROW_WITH_MESSAGE(action_queue.execute(), std::runtime_error, expected_message);
}


TEST(Action__BaseTest, execute__throws_an_exception_when_an_executed_queued_action_throws_an_exception)
{
   Blast::Action::Queue action_queue("MyQueue", { new ThrowsExceptionAction() });

   std::string expected_message = "Queue<MyQueue> error: The queued action \"ThrowsExceptionAction\" raised the following exception: \"ThrowsExceptionAction: Exception Thrown\"";
   ASSERT_THROW_WITH_MESSAGE(action_queue.execute(), std::runtime_error, expected_message);
}


TEST(Action__BaseTest, execute__executes_all_actions_in_the_queue)
{
   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction(), new TestAction() };
   Blast::Action::Queue action_queue("MyQueue", actions);

   for (auto &action : actions) ASSERT_FALSE(static_cast<TestAction *>(action)->executed);

   ASSERT_TRUE(action_queue.execute());

   for (auto &action : actions) ASSERT_TRUE(static_cast<TestAction *>(action)->executed);
}


TEST(Action__BaseTest, clear__deletes_all_actions_in_the_queue_and_empties_the_queue)
{
   ASSERT_EQ(0, TestAction::num_active);

   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction(), new TestAction() };

   ASSERT_EQ(3, TestAction::num_active);

   Blast::Action::Queue action_queue("MyQueue", actions);
   action_queue.clear();

   ASSERT_EQ(0, TestAction::num_active);
}


TEST(Action__BaseTest, on_destruction_deletes_all_actions_in_the_queue)
{
   ASSERT_EQ(0, TestAction::num_active);

   std::vector<Blast::Action::Base *> actions = { new TestAction(), new TestAction(), new TestAction() };

   ASSERT_EQ(3, TestAction::num_active);

   Blast::Action::Queue *action_queue = new Blast::Action::Queue("MyQueue", actions);
   delete action_queue;

   ASSERT_EQ(0, TestAction::num_active);
}


