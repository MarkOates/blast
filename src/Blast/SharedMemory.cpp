#ifdef BLAST_BUILD_WITH_BOOST


#include <Blast/SharedMemory.hpp>

#include <sstream>



namespace Blast
{



SharedMemory::SharedMemory(std::string location_identifier, int size, bool clear_on_launch)
   : shared_memory_object(boost::interprocess::open_or_create, location_identifier.c_str(), boost::interprocess::read_write)
   , mapped_region(shared_memory_object, boost::interprocess::read_write, 0, size)
   , location_identifier(location_identifier)
   , size(size)
   , clear_char('\0')
{
   shared_memory_object.truncate(size);

   if (clear_on_launch) clear();
}



SharedMemory::~SharedMemory()
{
   shared_memory_object.remove(location_identifier.c_str());
}



bool SharedMemory::set_mapped_region(std::string message)
{
   if (message.length() != size)
   {
      std::stringstream error_message;
      error_message << "SharedMemory: Message must be the same length (" << size << ") as the mapped memory region." << std::endl;
      std::runtime_error(error_message.str());
   }

   std::memset(mapped_region.get_address(), clear_char, mapped_region.get_size());

   char *mem = static_cast<char*>(mapped_region.get_address());
   for(std::size_t i = 0; i < message.size(); ++i)
   {
      *mem = message[i];
      mem++;
   }

   return true;
}



bool SharedMemory::write(std::string message)
{
   if (message.length() >= size)
   {
      std::stringstream error_message;
      error_message << "Message exceeds shared memory size of " << size << std::endl;
      throw std::runtime_error(error_message.str());
   }

   std::memset(mapped_region.get_address(), clear_char, mapped_region.get_size());

   char *mem = static_cast<char*>(mapped_region.get_address());
   for(std::size_t i = 0; i < message.size(); ++i)
   {
      *mem = message[i];
      mem++;
   }

   return true;
}



void SharedMemory::clear()
{
   char *address = (char *)mapped_region.get_address();
   size_t size = mapped_region.get_size();

   for (size_t i=0; i<size; i++) address[i] = clear_char;
}



std::string SharedMemory::get_location_identifier()
{
   return location_identifier;
}



int SharedMemory::get_size()
{
   return size;
}



char SharedMemory::get_clear_char()
{
   return clear_char;
}



std::string SharedMemory::get_mapped_region()
{
   std::string current_content(size, clear_char);
   char *mem = static_cast<char*>(mapped_region.get_address());
   for(std::size_t i = 0; i < mapped_region.get_size(); ++i) current_content[i] = *mem++;
   return current_content;
}



std::string SharedMemory::read()
{
   std::string s = get_mapped_region();

   size_t p = s.find_first_not_of(clear_char);
   s.erase(0, p);

   p = s.find_last_not_of(clear_char);
   if (std::string::npos != p)
      s.erase(p+1);

   return s;
}



bool SharedMemory::is_empty()
{
   char *mem = static_cast<char*>(mapped_region.get_address());
   for(std::size_t i=0; i<mapped_region.get_size(); ++i)
   {
      if (*mem != clear_char) return false;
      mem++;
   }
   return true;
}



} // namespace Blast


#endif   // #ifdef BLAST_BUILD_WITH_BOOST
