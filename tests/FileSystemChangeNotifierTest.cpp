

#include <gtest/gtest.h>

#include <Blast/FileSystemChangeNotifier.hpp>


TEST(FileSystemChangeNotifierTest, can_be_created)
{
   std::vector<std::string> paths = {};
   void(* callback)(std::string) = [](std::string path){};

   FileSystemChangeNotifier file_system_change_notifier(paths, callback);
}



