

#include <Blast/FileSystemChangeNotifier.hpp>

#include <iostream> // remove this!


void __watcher_callback(
      ConstFSEventStreamRef streamRef,
      void *clientCallBackInfo,
      size_t numEvents,
      void *eventPaths,
      const FSEventStreamEventFlags eventFlags[],
      const FSEventStreamEventId eventIds[])
{
   int i;
   //char **paths = char( **)eventPaths;

   printf("Callback called\n");
   for (i=0; i<numEvents; i++)
   {
      //int count;
      // flags are unsigned long, IDs are uint64_t
      //printf("Change %llu in %s, flags %lu\n", eventIds[i], paths[i], eventFlags[i]);
   }

   //my_actual_callback();
}


void FileSystemChangeNotifier::watcher_process()
{
   current_run_loop = CFRunLoopGetCurrent();
   CFStringRef mypath = CFSTR("./bin");
   CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&mypath, 1, NULL);
   FSEventStreamContext *callbackInfo = NULL;
   //FSEventStreamRef stream;
   CFAbsoluteTime latency = 0.01;

   stream = FSEventStreamCreate(NULL,
         &__watcher_callback,
         callbackInfo,
         pathsToWatch,
         kFSEventStreamEventIdSinceNow,
         latency,
         kFSEventStreamCreateFlagNone
         );

   FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
   FSEventStreamStart(stream);

   CFRunLoopRun();

   // shutdown (note this will flush all remaining events in the steam)
   FSEventStreamFlushSync(stream);
   FSEventStreamStop(stream);
   FSEventStreamInvalidate(stream);
   FSEventStreamRelease(stream);
}


FileSystemChangeNotifier::FileSystemChangeNotifier(std::vector<std::string> paths, void(* callback)(void))
   : current_run_loop(0)
   , stream()
   , paths(paths)
   , callback(callback)
   , watcher(nullptr)
{
   watcher = new std::thread(&FileSystemChangeNotifier::watcher_process, this);
}


FileSystemChangeNotifier::~FileSystemChangeNotifier()
{
   while (current_run_loop == 0) {
      std::cout << "FileSystemChangeNotifier: current_run_loop is not set" << std::endl;
      sleep(1);
   }

   CFRunLoopStop(current_run_loop);
   watcher->join();
   delete watcher;
}


