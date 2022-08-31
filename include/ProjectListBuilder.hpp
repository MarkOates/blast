#pragma once


#include <string>
#include <vector>


class ProjectListBuilder
{
private:
   std::string repos_directory;

protected:


public:
   ProjectListBuilder(std::string repos_directory="/Users/markoates/Repos/");
   ~ProjectListBuilder();

   std::string get_repos_directory() const;
   std::vector<std::string> get_directories();
};



