#pragma once


#include <string>


class CppPoolPatternGenerator
{
private:
   std::string class_name;

public:
   CppPoolPatternGenerator(std::string class_name="ClassName");
   ~CppPoolPatternGenerator();

   std::string generate_header_file_content();
   std::string generate_source_file_content();
};


