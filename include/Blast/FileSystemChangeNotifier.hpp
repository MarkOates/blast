#pragma once


#include <CoreServices/CoreServices.h>
#include <string>
#include <vector>
#include <thread>



class FileSystemChangeNotifier
{
private:
   CFRunLoopRef current_run_loop = 0;
   FSEventStreamRef stream;
   std::vector<std::string> paths;
   void(* callback)(void);

   void watcher_process();
   std::thread *watcher;

public:
   FileSystemChangeNotifier(std::vector<std::string> paths, void(* callback)(void));
   ~FileSystemChangeNotifier();
};


