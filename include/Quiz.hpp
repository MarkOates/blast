#pragma once


#include <Question.hpp>
#include <vector>


class Quiz
{
private:
   std::vector<Question> questions;

protected:


public:
   Quiz(std::vector<Question> questions={});
   ~Quiz();

   void set_questions(std::vector<Question> questions);
   std::vector<Question> get_questions() const;
   void append_questions(std::vector<Question> new_questions);
   void shuffle_questions();
};



