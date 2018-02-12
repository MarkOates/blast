

#include <Blast/CppPoolPatternGenerator.hpp>

#include <sstream>
#include <iostream>


static void __replace(std::string &str, const std::string &find_str, const std::string &replace_str)
{
  std::string::size_type pos = 0u;

  while((pos = str.find(find_str, pos)) != std::string::npos)
  {
     str.replace(pos, find_str.length(), replace_str);
     pos += replace_str.length();
  }
}


static const std::string pool_header_file_template = R"END(

#pragma once


#include <string>
#include <vector>
#include <CLASS.hpp>


class CLASSPool
{
public:
   enum find_option_t
   {
      FIND_OPTION_NONE = 0,
      FIND_OPTION_INCLUDE_NOT_FOUND,
      FIND_OPTION_RAISE_NOT_FOUND,
   };

   std::vector<CLASS *> pool;

   CLASSPool();
   ~CLASSPool();

   bool push_back(CLASS *base);
   bool remove(int id);
   bool destroy(int id);
   bool destroy_all();
   int count();

   CLASS *find(int id, find_option_t find_option=FIND_OPTION_NONE);
   //std::vector<CLASS *> select_by_ATTRIBUTE(ATTRIBUTE_TYPE ATTRIBUTE, find_option_t find_option=FIND_OPTION_NONE);
};


)END";


static const std::string pool_source_file_template = R"END(

#include <CLASSPool.hpp>

#include <sstream>


CLASSPool::CLASSPool()
   : pool()
{
}


CLASSPool::~CLASSPool()
{
}


bool CLASSPool::push_back(CLASS *element)
{
   pool.push_back(element);
   return true;
}


int CLASSPool::count()
{
   return pool.size();
}


CLASS *CLASSPool::find(int id, find_option_t find_option)
{
   CLASS *found_element = nullptr;

   for (auto &element : pool)
      if (element->get_id() == id) { found_element = element; break; }

   if (find_option == FIND_OPTION_RAISE_NOT_FOUND && found_element == nullptr)
   {
      std::stringstream error_message;
      error_message << "Looking for element with id = " << id << " but does not exist";
      throw std::runtime_error(error_message.str());
   }

   return found_element;
}


std::vector<CLASS *> CLASSPool::find(std::vector<int> ids, find_option_t find_option)
{
   std::vector<CLASS *> results = {};
   std::vector<int> not_found_ids = {};
   find_option_t find_option = (find_option == FIND_OPTION_RAISE_NOT_FOUND) ? FIND_OPTION_RAISE_NOT_FOUND : FIND_OPTION_NONE;

   for (unsigned i=0; i<ids.size(); i++)
   {
      try
      {
         CLASS *found_element = find(ids[i], find_option);
         if (found_element || (find_option == FIND_OPTION_INCLUDE_NOT_FOUND)) results.push_back(found_element);
      }
      catch (std::runtime_error const &e)
      {
         not_found_ids.push_back(ids[i]);
      }
   }

   if (!not_found_ids.empty())
   {
      std::stringstream error_message;
      error_message << "Looking for " << ids.size() << " element but only " << results.size() << " element found.";
      throw std::runtime_error(error_message.str());
   }

   return results;
}


/*
std::vector<CLASS *> CLASSPool::select_by_ATTRIBUTE(ATTRIBUTE_TYPE ATTRIBUTE, find_option_t find_option)
{
   std::vector<CLASS *> results = {};
   for (auto &pool_element : pool)
      if (pool_element.get_ATTRIBUTE() == ATTRIBUTE) results.push_back(pool_element);
   return results;
}
*/


bool CLASSPool::remove(int id)
{
   for (unsigned i=0; i<pool.size(); i++)
      if (pool[i]->get_id() == id)
      {
         pool.erase(pool.begin() + i);
         return true;
      }
   return false;
}


bool CLASSPool::destroy(int id)
{
   for (unsigned i=0; i<pool.size(); i++)
      if (pool[i]->get_id() == id)
      {
         delete pool[i];
         return true;
      }
   return false;
}


bool CLASSPool::destroy_all()
{
   for (unsigned i=0; i<pool.size(); i++) delete pool[i];
   pool.clear();
   return true;
}


)END";


CppPoolPatternGenerator::CppPoolPatternGenerator(std::string class_name)
   : class_name(class_name)
{
}


CppPoolPatternGenerator::~CppPoolPatternGenerator()
{
}


std::string CppPoolPatternGenerator::generate_header_file_content()
{
   std::string result = pool_header_file_template;
   __replace(result, "CLASS", class_name);
   return result;
}


std::string CppPoolPatternGenerator::generate_source_file_content()
{
   std::string result = pool_source_file_template;
   __replace(result, "CLASS", class_name);
   return result;
}


