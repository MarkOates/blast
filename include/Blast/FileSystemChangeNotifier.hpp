#pragma once


#include <string>
#include <vector>


class FileSystemChangeNotifier
{
private:
   class Implementation;
   std::vector<std::string> paths;
   void(* callback)(std::string path);
   std::unique_ptr<Implementation> implementation;

public:
   FileSystemChangeNotifier(std::vector<std::string> paths, void(* callback)(std::string));
   ~FileSystemChangeNotifier();
};


