#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Blast/Quintessence/YAMLParsers/QuintessenceParser.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/DeveloperSystem.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>


namespace
{
   std::string normalize_line_endings(std::string str)
   {
      str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
      return str;
   }

   std::string get_next_sandbox_dir()
   {
      std::filesystem::path tmp_dir = Blast::DeveloperSystem().infer_projects_directory() + "blast/tmp";
      std::filesystem::create_directories(tmp_dir);
      int max_num = 0;
      for (const auto& entry : std::filesystem::directory_iterator(tmp_dir))
      {
         if (entry.is_directory())
         {
            std::string dir_name = entry.path().filename().string();
            if (dir_name.rfind("sandbox_", 0) == 0 && dir_name.length() == 13) // "sandbox_" + 5 digits
            {
               try
               {
                  int num = std::stoi(dir_name.substr(8));
                  if (num > max_num) max_num = num;
               }
               catch (...) {}
            }
         }
      }
      int next_num = max_num + 1;
      std::stringstream ss;
      ss << "sandbox_" << std::setw(5) << std::setfill('0') << next_num;
      return (tmp_dir / ss.str()).string();
   }

   void run_integration_test(const std::string &fixture_name)
   {
      std::string project_root = Blast::DeveloperSystem().infer_projects_directory() + "blast";

      // 1. Determine and create the unique temporary sandbox directory under project-local tmp/
      std::filesystem::path temp_dir = get_next_sandbox_dir();
      std::filesystem::create_directories(temp_dir);

      // Ensure the temp directory exists or FAIL immediately
      bool temp_dir_exists = std::filesystem::exists(temp_dir) && std::filesystem::is_directory(temp_dir);
      ASSERT_TRUE(temp_dir_exists) << "Failed to create temporary directory: " << temp_dir.string();

      // Print debugging info about the sandbox
      std::cout << "[SANDBOX] Created dynamic directory: " << temp_dir.string() << std::endl;

      // 2. Compile the test helper program using the real Makefile directly into the sandbox
      std::filesystem::path test_binary = temp_dir / "quintessence_from_yaml_for_tests";
      std::stringstream compile_cmd;
      compile_cmd << "make -C " << project_root << " " << test_binary.string() 
                  << " TEST_BINARY_OUTPUT_PATH=" << test_binary.string();

      Blast::ShellCommandExecutorWithCallback compile_executor(
         compile_cmd.str(), 
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
      std::string compile_output = compile_executor.execute();
      ASSERT_TRUE(std::filesystem::exists(test_binary)) 
         << "Failed to compile test helper binary! Output:\n" << compile_output;

      // 3. Create 'quintessence/quintessences' folders inside the sandbox
      std::filesystem::path sandbox_fixture_dir = temp_dir / "quintessence/quintessences";
      std::filesystem::create_directories(sandbox_fixture_dir);

      // 4. Copy the baseline fixture file into the sandbox
      std::filesystem::path source_fixture = std::filesystem::path(project_root) / 
         "tests/fixtures/quintessence/quintessences" / (fixture_name + ".q.yml");
      std::filesystem::path target_fixture = sandbox_fixture_dir / (fixture_name + ".q.yml");
      ASSERT_TRUE(std::filesystem::exists(source_fixture)) << "Source fixture missing: " << source_fixture.string();
      
      std::filesystem::copy(source_fixture, target_fixture);
      ASSERT_TRUE(std::filesystem::exists(target_fixture)) << "Failed to copy fixture: " << target_fixture.string();

      // 5. Execute our sandboxed binary inside the sandbox using a shell command chain
      std::stringstream run_command;
      run_command << "cd " << temp_dir.string()
                  << " && ./quintessence_from_yaml_for_tests -f quintessence/quintessences/"
                  << fixture_name << ".q.yml";

      Blast::ShellCommandExecutorWithCallback run_executor(
         run_command.str(), 
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
      std::string run_output = run_executor.execute();

      // 6. Verify outputs exist in sandbox
      std::filesystem::path generated_header = temp_dir / "include/quintessences" / (fixture_name + ".hpp");
      std::filesystem::path generated_source = temp_dir / "src/quintessences" / (fixture_name + ".cpp");

      EXPECT_TRUE(std::filesystem::exists(generated_header)) 
         << "Header was not generated in sandbox: " << generated_header.string();
      EXPECT_TRUE(std::filesystem::exists(generated_source)) 
         << "Source was not generated in sandbox: " << generated_source.string();

      // 7. Verify sandbox content matches goldens
      std::filesystem::path golden_header = std::filesystem::path(project_root) / 
         "tests/fixtures/quintessence/goldens" / (fixture_name + ".hpp");
      std::filesystem::path golden_source = std::filesystem::path(project_root) / 
         "tests/fixtures/quintessence/goldens" / (fixture_name + ".cpp");

      ASSERT_TRUE(std::filesystem::exists(golden_header)) << "Golden header missing: " << golden_header.string();
      ASSERT_TRUE(std::filesystem::exists(golden_source)) << "Golden source missing: " << golden_source.string();

      auto read_file = [](const std::filesystem::path &path) -> std::string {
         std::ifstream ifs(path);
         return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
      };

      std::string expected_header_content = normalize_line_endings(read_file(golden_header));
      std::string actual_header_content = normalize_line_endings(read_file(generated_header));
      EXPECT_EQ(expected_header_content, actual_header_content) 
         << "Header content mismatch for fixture: " << fixture_name;

      std::string expected_source_content = normalize_line_endings(read_file(golden_source));
      std::string actual_source_content = normalize_line_endings(read_file(generated_source));
      EXPECT_EQ(expected_source_content, actual_source_content) 
         << "Source content mismatch for fixture: " << fixture_name;
   }
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest, can_be_created_without_blowing_up)
{
   Blast::Quintessence::YAMLParsers::QuintessenceParser quintessence_parser;
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest, parse__returns_a_default_class_instance_for_now)
{
   Blast::Quintessence::YAMLParsers::QuintessenceParser quintessence_parser;
   Blast::Cpp::Class parsed_class = quintessence_parser.parse();
   EXPECT_EQ("UnnamedClass", parsed_class.get_class_name());
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_StringSplitter_fixture)
{
   run_integration_test("StringSplitter");
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_GodObject_fixture)
{
   run_integration_test("GodObject");
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_EnumObject_fixture)
{
   run_integration_test("EnumObject");
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_InheritanceObject_fixture)
{
   run_integration_test("InheritanceObject");
}


TEST(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_MethodsObject_fixture)
{
   run_integration_test("MethodsObject");
}
