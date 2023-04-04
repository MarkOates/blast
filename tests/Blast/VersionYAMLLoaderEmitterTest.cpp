
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Blast/VersionYAMLLoaderEmitter.hpp>

#include <Blast/Testing/TemporaryDirectoryCreator.hpp>
#include <Blast/Testing/ErrorAssertions.hpp>


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


TEST(Blast_VersionYAMLLoaderEmitterTest, load__with_invalid_labels__will_throw_an_error)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version-with_invalid_labels.yml";
   Blast::VersionYAMLLoaderEmitter version_yamlloader_emitter(TEST_YAML_VERSION_FILE);
   ASSERT_THROW_WITH_MESSAGE(
      version_yamlloader_emitter.load(),
      std::runtime_error,
      "[Blast::VersionYAMLLoaderEmitter] error: The following labels are invalid: \"  \", \"&%\", \"-wip\", "
   );
}


TEST(Blast_VersionYAMLLoaderEmitterTest, load__with_invalid_metadata__will_throw_an_error)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version-with_invalid_metadata.yml";
   Blast::VersionYAMLLoaderEmitter version_yamlloader_emitter(TEST_YAML_VERSION_FILE);
   ASSERT_THROW_WITH_MESSAGE(
      version_yamlloader_emitter.load(),
      std::runtime_error,
      "[Blast::VersionYAMLLoaderEmitter] error: The following labels are invalid: \" \n\", \"#$\", \"5\", "
   );
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


TEST(Blast_VersionYAMLLoaderEmitterTest, increment__will_increment_the_patch_number)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();
   EXPECT_EQ(13, loader.get_patch());

   loader.increment();

   EXPECT_EQ(14, loader.get_patch());
}


TEST(Blast_VersionYAMLLoaderEmitterTest, increment__when_the_patch_number_is_even__will_add_a_wip_label)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();
   EXPECT_EQ(13, loader.get_patch());

   loader.increment();

   EXPECT_THAT(loader.get_labels(), ::testing::Contains("wip"));
}


TEST(Blast_VersionYAMLLoaderEmitterTest, increment__when_the_patch_number_is_odd__will_remove_a_wip_label)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();
   EXPECT_EQ(13, loader.get_patch());

   loader.increment();
   loader.increment();

   EXPECT_THAT(loader.get_labels(), ::testing::Not(::testing::Contains("wip")));
}


TEST(Blast_VersionYAMLLoaderEmitterTest, add_label__will_add_a_label)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();

   loader.add_label("foo");
   loader.add_label("bar");
   loader.add_label("bazz");

   std::set<std::string> expected_labels = std::set<std::string>{ "wip", "foo", "bar", "bazz" };
   std::set<std::string> actual_labels = loader.get_labels();

   EXPECT_EQ(expected_labels, actual_labels);
}


TEST(Blast_VersionYAMLLoaderEmitterTest, add_metadata__will_add_a_metadata)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();

   loader.add_metadata("foo");
   loader.add_metadata("bar");
   loader.add_metadata("bazz");

   std::set<std::string> expected_metadata = std::set<std::string>{ "foo", "bar", "bazz" };
   std::set<std::string> actual_metadata = loader.get_metadata();

   EXPECT_EQ(expected_metadata, actual_metadata);
}


TEST(Blast_VersionYAMLLoaderEmitterTest, increment__will_clear_any_prior_labels_and_metadata)
{
   std::string TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   Blast::VersionYAMLLoaderEmitter loader(TEST_YAML_VERSION_FILE);
   loader.load();

   loader.add_label("foo");
   loader.add_label("buz");
   loader.increment();

   std::set<std::string> expected_labels_after_increment = { "wip" };
   std::set<std::string> expected_metadata_after_increment = {};
   std::set<std::string> actual_labels_after_increment = loader.get_labels();
   std::set<std::string> actual_metadata_after_increment = loader.get_metadata();

   EXPECT_EQ(expected_labels_after_increment, actual_labels_after_increment);
   EXPECT_EQ(expected_metadata_after_increment, actual_metadata_after_increment);
}


TEST(Blast_VersionYAMLLoaderEmitterTest, save__will_overwrite_the_file)
{
   std::string SOURCE_TEST_YAML_VERSION_FILE = TEST_FIXTURES_PATH "version.yml";
   std::filesystem::path temporary_directory = Blast::Testing::TemporaryDirectoryCreator().create();
   std::string DESTRUCTIVE_TEST_YAML_VERSION_FILE = temporary_directory.string() + "/version.yml";
   std::filesystem::copy(SOURCE_TEST_YAML_VERSION_FILE, DESTRUCTIVE_TEST_YAML_VERSION_FILE);

   Blast::VersionYAMLLoaderEmitter loader(DESTRUCTIVE_TEST_YAML_VERSION_FILE);
   loader.load();
   loader.increment();
   loader.increment();
   loader.save();

   std::stringstream result_yaml_stream;
   YAML::Node result_yaml_node = YAML::LoadFile(DESTRUCTIVE_TEST_YAML_VERSION_FILE);
   YAML::Emitter emitter(result_yaml_stream);
   emitter << result_yaml_node;
   std::string result_yaml = result_yaml_stream.str();

   std::string expected_result_yaml = R"(note: This is a machine generated file. Do not modify.
version:
  major: 3
  minor: 7
  patch: 15
  labels: []
  metadata: [])";

   std::string actual_result_yaml = result_yaml;

   EXPECT_EQ(expected_result_yaml, actual_result_yaml);
}


