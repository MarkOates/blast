

#include <Blast/FileSystemChangeNotifier.hpp>


#include <fstream>
#include <iostream>


int main(int argc, char *argv[])
{
   std::vector<std::string> paths = { "./bin/examples" };

   FileSystemChangeNotifier file_system_change_notifier(paths, []{
      std::cout << "File changed in the folder!" << std::endl;
   });

   std::ofstream myfile;
   myfile.open("./bin/examples/test_file.txt");
   myfile << "Writing this to a file.\n";
   myfile.close();

   return 0;
}


