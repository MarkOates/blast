

#include <Quizes/MultiplexQuestion.hpp>




namespace Quizes
{


MultiplexQuestion::MultiplexQuestion(std::string date, std::string subject, std::string subject_type, std::string relevance, std::string reference_page)
   : date(date)
   , subject(subject)
   , subject_type(subject_type)
   , relevance(relevance)
   , reference_page(reference_page)
{
}


MultiplexQuestion::~MultiplexQuestion()
{
}


void MultiplexQuestion::set_date(std::string date)
{
   this->date = date;
}


void MultiplexQuestion::set_subject(std::string subject)
{
   this->subject = subject;
}


void MultiplexQuestion::set_subject_type(std::string subject_type)
{
   this->subject_type = subject_type;
}


void MultiplexQuestion::set_relevance(std::string relevance)
{
   this->relevance = relevance;
}


void MultiplexQuestion::set_reference_page(std::string reference_page)
{
   this->reference_page = reference_page;
}


std::string MultiplexQuestion::get_date() const
{
   return date;
}


std::string MultiplexQuestion::get_subject() const
{
   return subject;
}


std::string MultiplexQuestion::get_subject_type() const
{
   return subject_type;
}


std::string MultiplexQuestion::get_relevance() const
{
   return relevance;
}


std::string MultiplexQuestion::get_reference_page() const
{
   return reference_page;
}




} // namespace Quizes


