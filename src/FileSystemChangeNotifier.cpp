

#include <Blast/FileSystemChangeNotifier.hpp>

#include <CoreServices/CoreServices.h>
#include <thread>


class FileSystemChangeNotifier::Implementation
{
private:
   FileSystemChangeNotifier *notifier;
   FSEventStreamRef stream;
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

public:
   CFRunLoopRef current_run_loop = 0;

   Implementation(FileSystemChangeNotifier *notifier);
   ~Implementation();
   void initialize();
};


FileSystemChangeNotifier::Implementation::Implementation(FileSystemChangeNotifier *notifier)
   : notifier(notifier)
   , stream()
   , watcher(nullptr)
   , current_run_loop(0)
{ }


void FileSystemChangeNotifier::Implementation::initialize()
{
   watcher = new std::thread(&FileSystemChangeNotifier::Implementation::watcher_process, this);
   while (current_run_loop == 0) {}
}


FileSystemChangeNotifier::Implementation::~Implementation()
{
   CFRunLoopStop(current_run_loop);
   watcher->join();
   delete watcher;
}


void FileSystemChangeNotifier::Implementation::__watcher_callback(
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


void FileSystemChangeNotifier::Implementation::watcher_process()
{
   CFStringRef strs[notifier->paths.size()];
   for (int i=0; i<notifier->paths.size(); i++)
   {
      CFStringRef cf_string_ref = CFStringCreateWithCString(NULL, notifier->paths[i].c_str(), kCFStringEncodingMacRoman);
      strs[i] = cf_string_ref;
   }

   CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&strs, notifier->paths.size(), NULL);
   FSEventStreamContext callbackInfo = {NULL, this->notifier, NULL, NULL, NULL};
   CFAbsoluteTime latency = 0.01;

   stream = FSEventStreamCreate(NULL,
         &FileSystemChangeNotifier::Implementation::__watcher_callback,
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
   : paths(paths)
   , callback(callback)
   , implementation(new Implementation(this))
{
   implementation->initialize();
}


FileSystemChangeNotifier::~FileSystemChangeNotifier()
{
}


