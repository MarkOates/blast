#pragma once


#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>


namespace Blast
{
   class SharedMemory
   {
   private:
      boost::interprocess::shared_memory_object shared_memory_object;
      boost::interprocess::mapped_region mapped_region;
      std::string location_identifier;
      int size;
      char clear_char;

   public:
      SharedMemory(std::string location_identifier="shared", int size=256, bool clear_on_launch=true);
      ~SharedMemory();

      bool set_mapped_region(std::string message);

      std::string get_mapped_region();
      std::string get_location_identifier();
      int get_size();
      char get_clear_char();

      bool write(std::string message);
      void clear();

      std::string read();
      bool is_empty();
   };
}


