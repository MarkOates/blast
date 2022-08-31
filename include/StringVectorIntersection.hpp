#pragma once


#include <string>
#include <vector>


class StringVectorIntersection
{
private:
   std::vector<std::string> v1;
   std::vector<std::string> v2;

protected:


public:
   StringVectorIntersection(std::vector<std::string> v1={}, std::vector<std::string> v2={});
   ~StringVectorIntersection();

   std::vector<std::string> intersection();
};



