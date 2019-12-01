

#include <gtest/gtest.h>

#include <Blast/Quintessence/ComponentGenerator.hpp>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(Blast_Quintessence_ComponentGenerator, can_be_created_without_blowing_up)
{
   ComponentGenerator generator;
}


