

#include <Blast/FileSystemChangeNotifier.hpp>


void FileSystemChangeNotifier::__watcher_callback(
      ConstFSEventStreamRef streamRef,
      void *clientCallBackInfo,
      size_t numEvents,
      void *eventPaths,
      const FSEventStreamEventFlags eventFlags[],
      const FSEventStreamEventId eventIds[])
{
   char **paths = (char **)eventPaths;

   FileSystemChangeNotifier *file_system_change_notifier = static_cast<FileSystemChangeNotifier *>(clientCallBackInfo);

   if (file_system_change_notifier->callback)
   {
      for (int i=0; i<numEvents; i++)
      {
         // flags are unsigned long, IDs are uint64_t
         // printf("---");
         // printf("event id %llu\n", eventIds[i]);
         // printf("path %s\n", paths[i]);
         // printf("flag %u\n", eventFlags[i]);
         std::string path = paths[i];
         file_system_change_notifier->callback(path);
      }
   }
}


void FileSystemChangeNotifier::watcher_process()
{
   CFStringRef strs[paths.size()];
   for (int i=0; i<paths.size(); i++)
   {
      CFStringRef cf_string_ref = CFStringCreateWithCString(NULL, paths[i].c_str(), kCFStringEncodingMacRoman);
      strs[i] = cf_string_ref;
   }

   CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&strs, paths.size(), NULL);
   FSEventStreamContext callbackInfo = {NULL, this, NULL, NULL, NULL};
   CFAbsoluteTime latency = 0.01;

   stream = FSEventStreamCreate(NULL,
         &FileSystemChangeNotifier::__watcher_callback,
         &callbackInfo,
         pathsToWatch,
         kFSEventStreamEventIdSinceNow,
         latency,
         kFSEventStreamCreateFlagNone
         );

   FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
   FSEventStreamStart(stream);

   current_run_loop = CFRunLoopGetCurrent();

   CFRunLoopRun();

   FSEventStreamFlushSync(stream);
   FSEventStreamStop(stream);
   FSEventStreamInvalidate(stream);
   FSEventStreamRelease(stream);
}


FileSystemChangeNotifier::FileSystemChangeNotifier(std::vector<std::string> paths, void(* callback)(std::string path))
   : current_run_loop(0)
   , stream()
   , paths(paths)
   , watcher(nullptr)
   , callback(callback)
{
   watcher = new std::thread(&FileSystemChangeNotifier::watcher_process, this);
   while (current_run_loop == 0) {}
}


FileSystemChangeNotifier::~FileSystemChangeNotifier()
{
   CFRunLoopStop(current_run_loop);
   watcher->join();
   delete watcher;
}


