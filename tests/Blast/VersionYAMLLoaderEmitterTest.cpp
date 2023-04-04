
#include <gtest/gtest.h>

#include <Blast/VersionYAMLLoaderEmitter.hpp>


#ifdef _WIN32
#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/blast/tests/fixtures/"
#else
#define TEST_FIXTURES_PATH "/Users/markoates/Repos/blast/tests/fixtures/"
#endif


TEST(Blast_VersionYAMLLoaderEmitterTest, can_be_created_without_blowing_up)
{
   Blast::VersionYAMLLoaderEmitter version_yamlloader_emitter;
}


TEST(Blast_VersionYAMLLoaderEmitterTest, load__will_not_blow_up)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter version_yamlloader_emitter(TEST_YAML_VERSION_FILE);
   version_yamlloader_emitter.load();
}


TEST(Blast_VersionYAMLLoaderEmitterTest, load__when_the_loaded_yaml_does_not_contain_the_expected_keys__throws_an_error)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter version_yamlloader_emitter(TEST_YAML_VERSION_FILE);
   version_yamlloader_emitter.load();
}


TEST(Blast_VersionYAMLLoaderEmitterTest, load__will_extract_the_version_info_from_the_file)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();
   EXPECT_EQ(3, loader.get_major());
   EXPECT_EQ(7, loader.get_minor());
   EXPECT_EQ(13, loader.get_patch());
}


