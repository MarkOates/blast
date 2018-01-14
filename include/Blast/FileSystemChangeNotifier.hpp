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
   static void __watcher_callback(
         ConstFSEventStreamRef streamRef,
         void *clientCallBackInfo,
         size_t numEvents,
         void *eventPaths,
         const FSEventStreamEventFlags eventFlags[],
         const FSEventStreamEventId eventIds[]
      );

   void watcher_process();
   std::thread *watcher;
   void(* callback)(std::string path);

public:
   FileSystemChangeNotifier(std::vector<std::string> paths, void(* callback)(std::string));
   ~FileSystemChangeNotifier();
};


