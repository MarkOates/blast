#include <gtest/gtest.h>


#include <Blast/SharedMemory.hpp>


TEST(SharedMemoryTest, can_be_created)
{
   Blast::SharedMemory shared_memory;
}


TEST(SharedMemoryTest, when_created_sets_the_shared_memory_location_identifier_to_the_expected_value)
{
   Blast::SharedMemory shared_memory;

   ASSERT_EQ("shared", shared_memory.get_location_identifier());
   ASSERT_EQ(256, shared_memory.get_size());
}


TEST(SharedMemoryTest, when_created_sets_the_shared_memory_location_identifier_to_the_initialized_arguments)
{
   Blast::SharedMemory shared_memory("my_magical_shared_memory", 128);

   ASSERT_EQ("my_magical_shared_memory", shared_memory.get_location_identifier());
   ASSERT_EQ(128, shared_memory.get_size());
}


TEST(SharedMemoryTest, can_set_and_get_a_shared_memory)
{
   std::string expected_string("Hello World!\0\0\0\0", 16);

   Blast::SharedMemory shared_memoryA("my_magical_shared_memory", 16);
   Blast::SharedMemory shared_memoryB("my_magical_shared_memory", 16);

   ASSERT_TRUE(shared_memoryA.set_mapped_region(expected_string));
   ASSERT_EQ(expected_string, shared_memoryB.get_mapped_region());
}


TEST(SharedMemoryTest, when_setting_a_mapped_region_with_a_string_ne_to_the_size_of_the_mapped_region_throws_an_exception)
{
   std::string expected_string("Hello World!\0\0\0\0", 16);

   Blast::SharedMemory shared_memoryA("my_magical_shared_memory", 16);
   Blast::SharedMemory shared_memoryB("my_magical_shared_memory", 16);

   ASSERT_TRUE(shared_memoryA.set_mapped_region(expected_string));
   ASSERT_EQ(expected_string, shared_memoryB.get_mapped_region());
}


TEST(SharedMemoryTest, can_read_and_write_strings_to_and_from_a_shared_memory)
{
   std::string expected_string = "Hello World!";

   Blast::SharedMemory shared_memoryA("my_magical_shared_memory", 16);
   Blast::SharedMemory shared_memoryB("my_magical_shared_memory", 16);

   ASSERT_TRUE(shared_memoryA.write(expected_string));
   ASSERT_EQ(expected_string, shared_memoryB.read());
}


TEST(SharedMemoryTest, when_writing_a_string_that_is_longer_than_shared_memory_size_throws_an_exception)
{
   std::string expected_string = "this string is much longer than 16 characters";

   Blast::SharedMemory shared_memory("my_magical_shared_memory", 16);

   ASSERT_THROW(shared_memory.write(expected_string), std::runtime_error);
}


TEST(DISABLED_SharedMemoryTest, can_set_and_get_across_shared_memory_processes)
{
   // TODO
}
