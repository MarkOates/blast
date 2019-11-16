
#include <gtest/gtest.h>

#include <Blast/ProjectComponentLister.hpp>

TEST(Blast_ProjectComponentListerTest, run__can_be_created_without_blowing_up)
{
   Blast::ProjectComponentLister lister;
}
