

#include <Blast/FileSystemChangeNotifier.hpp>

#include <iostream>
#include <sstream>


int main(int argc, char *argv[])
{
   std::vector<std::string> paths = { "./bin/foo", "./bin/bar" };

   FileSystemChangeNotifier file_system_change_notifier(paths, [](std::string path){
      std::cout << "A file was changed in " << path << std::endl;
   });

   std::stringstream path_strs;
   for (auto &path : paths) path_strs << path << " ";
   std::cout << "Currently watching for file changes in " << path_strs.str() << std::endl;
   std::cout << "Enter any characters to quit." << std::endl;

   int i;
   std::cin >> i;

   return 0;
}


