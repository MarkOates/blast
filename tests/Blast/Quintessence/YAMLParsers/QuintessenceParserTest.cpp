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


class Blast_Quintessence_YAMLParsers_QuintessenceParserTest : public ::testing::Test
{
protected:
   std::string project_root;

   void SetUp() override
   {
      project_root = Blast::DeveloperSystem().infer_projects_directory() + "blast";
   }

   std::string normalize_line_endings(std::string str)
   {
      str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
      return str;
   }

   std::string get_next_sandbox_dir()
   {
      static int current_max_num = -1;
      std::filesystem::path tmp_dir = Blast::DeveloperSystem().infer_projects_directory() + "blast/tmp";
      std::filesystem::create_directories(tmp_dir);
      
      if (current_max_num == -1)
      {
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
         current_max_num = max_num;
      }

      current_max_num++;
      std::stringstream ss;
      ss << "sandbox_" << std::setw(5) << std::setfill('0') << current_max_num;
      return (tmp_dir / ss.str()).string();
   }

   std::filesystem::path create_sandbox_and_compile_helper()
   {
      std::filesystem::path temp_dir = get_next_sandbox_dir();
      std::filesystem::create_directories(temp_dir);

      bool temp_dir_exists = std::filesystem::exists(temp_dir) && std::filesystem::is_directory(temp_dir);
      if (!temp_dir_exists)
      {
         ADD_FAILURE() << "Failed to create temporary directory: " << temp_dir.string();
         return "";
      }

      std::cout << "[SANDBOX] Created dynamic directory: " << temp_dir.string() << std::endl;

      std::filesystem::path test_binary = temp_dir / "quintessence_from_yaml_for_tests";
      std::stringstream compile_cmd;
      compile_cmd << "make -C " << project_root << " " << test_binary.string() 
                  << " TEST_BINARY_OUTPUT_PATH=" << test_binary.string();

      Blast::ShellCommandExecutorWithCallback compile_executor(
         compile_cmd.str(), 
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
      std::string compile_output = compile_executor.execute();
      if (!std::filesystem::exists(test_binary))
      {
         ADD_FAILURE() << "Failed to compile test helper binary! Output:\n" << compile_output;
         return "";
      }

      return temp_dir;
   }

   void run_integration_test(const std::string &fixture_name)
   {
      std::filesystem::path temp_dir = create_sandbox_and_compile_helper();
      ASSERT_FALSE(temp_dir.empty());

      std::filesystem::path sandbox_fixture_dir = temp_dir / "quintessence/quintessences";
      std::filesystem::create_directories(sandbox_fixture_dir);

      std::filesystem::path source_fixture = std::filesystem::path(project_root) / 
         "tests/fixtures/quintessence/quintessences" / (fixture_name + ".q.yml");
      std::filesystem::path target_fixture = sandbox_fixture_dir / (fixture_name + ".q.yml");
      ASSERT_TRUE(std::filesystem::exists(source_fixture)) << "Source fixture missing: " << source_fixture.string();
      
      std::filesystem::copy(source_fixture, target_fixture);
      ASSERT_TRUE(std::filesystem::exists(target_fixture)) << "Failed to copy fixture: " << target_fixture.string();

      std::stringstream run_command;
      run_command << "cd " << temp_dir.string()
                  << " && ./quintessence_from_yaml_for_tests -f quintessence/quintessences/"
                  << fixture_name << ".q.yml";

      Blast::ShellCommandExecutorWithCallback run_executor(
         run_command.str(), 
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
      std::string run_output = run_executor.execute();

      std::filesystem::path generated_header = temp_dir / "include/quintessences" / (fixture_name + ".hpp");
      std::filesystem::path generated_source = temp_dir / "src/quintessences" / (fixture_name + ".cpp");

      EXPECT_TRUE(std::filesystem::exists(generated_header)) 
         << "Header was not generated in sandbox: " << generated_header.string();
      EXPECT_TRUE(std::filesystem::exists(generated_source)) 
         << "Source was not generated in sandbox: " << generated_source.string();

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

   void run_negative_integration_test(const std::string &fixture_name, const std::string &expected_error_message)
   {
      std::filesystem::path temp_dir = create_sandbox_and_compile_helper();
      ASSERT_FALSE(temp_dir.empty());

      std::filesystem::path sandbox_fixture_dir = temp_dir / "quintessence/quintessences/negative";
      std::filesystem::create_directories(sandbox_fixture_dir);

      std::filesystem::path source_fixture = std::filesystem::path(project_root) / 
         "tests/fixtures/quintessence/quintessences/negative" / (fixture_name + ".q.yml");
      std::filesystem::path target_fixture = sandbox_fixture_dir / (fixture_name + ".q.yml");
      ASSERT_TRUE(std::filesystem::exists(source_fixture)) << "Source fixture missing: " << source_fixture.string();
      
      std::filesystem::copy(source_fixture, target_fixture);
      ASSERT_TRUE(std::filesystem::exists(target_fixture)) << "Failed to copy fixture: " << target_fixture.string();

      std::stringstream run_command;
      run_command << "cd " << temp_dir.string()
                  << " && ./quintessence_from_yaml_for_tests -f quintessence/quintessences/negative/"
                  << fixture_name << ".q.yml";

      Blast::ShellCommandExecutorWithCallback run_executor(
         run_command.str(), 
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback,
         true // capture_stderr
      );
      std::string run_output = run_executor.execute();

      EXPECT_FALSE(run_executor.get_executed_successfully()) 
         << "Expected execution to fail, but it succeeded for: " << fixture_name;

      std::string normalized_output = normalize_line_endings(run_output);
      EXPECT_THAT(normalized_output, ::testing::HasSubstr(expected_error_message)) 
         << "Expected error message was not found in output!\n"
         << "Actual output: \n" << run_output;

      std::filesystem::path generated_header = temp_dir / "include/quintessences" / (fixture_name + ".hpp");
      std::filesystem::path generated_source = temp_dir / "src/quintessences" / (fixture_name + ".cpp");
      EXPECT_FALSE(std::filesystem::exists(generated_header)) 
         << "Header was unexpectedly generated: " << generated_header.string();
      EXPECT_FALSE(std::filesystem::exists(generated_source)) 
         << "Source was unexpectedly generated: " << generated_source.string();

      std::filesystem::remove_all(temp_dir);
   }
};


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest, can_be_created_without_blowing_up)
{
   Blast::Quintessence::YAMLParsers::QuintessenceParser quintessence_parser;
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest, parse__returns_a_default_class_instance_for_now)
{
   Blast::Quintessence::YAMLParsers::QuintessenceParser quintessence_parser;
   Blast::Cpp::Class parsed_class = quintessence_parser.parse();
   EXPECT_EQ("UnnamedClass", parsed_class.get_class_name());
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_StringSplitter_fixture)
{
   run_integration_test("StringSplitter");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_GodObject_fixture)
{
   run_integration_test("GodObject");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_EnumObject_fixture)
{
   run_integration_test("EnumObject");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_InheritanceObject_fixture)
{
   run_integration_test("InheritanceObject");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__runs_successfully_on_MethodsObject_fixture)
{
   run_integration_test("MethodsObject");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_InvalidYaml_fixture)
{
   run_negative_integration_test("InvalidYaml", "ERROR: YAML Parse Failure");
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MissingMethodBody_fixture)
{
   std::string expected_err = "[extract_function_body_dependency_symbols] parse failure: For this element";
   run_negative_integration_test("MissingMethodBody", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_InvalidGetter_fixture)
{
   std::string expected_err = "Attribute property \"getter\" can only be one of";
   run_negative_integration_test("InvalidGetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MissingExplicitGetterMethod_fixture)
{
   std::string expected_err = "explicit getters have been set on some properties, yet the expected function";
   run_negative_integration_test("MissingExplicitGetterMethod", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MissingDependency_fixture)
{
   std::string expected_err = "error: Could not find [ MissingType] dependency(s)";
   run_negative_integration_test("MissingDependency", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MultipleDestructors_fixture)
{
   std::string expected_err = "More than one destructor (function prefixed with '~') is present.";
   run_negative_integration_test("MultipleDestructors", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_UnexpectedTypeNode_fixture)
{
   std::string expected_err = "Unexpected type_node, expected to be of YAML type Scalar.";
   run_negative_integration_test("UnexpectedTypeNode", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_UnexpectedNameNode_fixture)
{
   std::string expected_err = "Unexpected name_node, expected to be of YAML type Scalar.";
   run_negative_integration_test("UnexpectedNameNode", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_UnexpectedDefaultArgumentNode_fixture)
{
   std::string expected_err = "Unexpected default_argument_node, expected to be of YAML type Scalar.";
   run_negative_integration_test("UnexpectedDefaultArgumentNode", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_UnexpectedParameterSequenceElement_fixture)
{
   std::string expected_err = "Unexpected sequence element in \"parameters\", expected to be of a YAML Map.";
   run_negative_integration_test("UnexpectedParameterSequenceElement", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesNotSequence_fixture)
{
   std::string expected_err = "unexpected type expecting YAML:: 3";
   run_negative_integration_test("ParentClassesNotSequence", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesSequenceElementNotMap_fixture)
{
   std::string expected_err = "Unexpected sequence element in \"parent_classes\", expected to be of a YAML Map.";
   run_negative_integration_test("ParentClassesSequenceElementNotMap", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesMissingClass_fixture)
{
   std::string expected_err = "Missing required key 'class' in parent_classes.";
   run_negative_integration_test("ParentClassesMissingClass", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesClassNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for 'class' in parent_classes, expected to be of YAML type Scalar.";
   run_negative_integration_test("ParentClassesClassNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesMissingScope_fixture)
{
   std::string expected_err = "Missing required key 'scope' in parent_classes.";
   run_negative_integration_test("ParentClassesMissingScope", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesScopeNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for 'scope' in parent_classes, expected to be of YAML type Scalar.";
   run_negative_integration_test("ParentClassesScopeNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesMissingInitWith_fixture)
{
   std::string expected_err = "Missing required key 'init_with' in parent_classes.";
   run_negative_integration_test("ParentClassesMissingInitWith", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ParentClassesInitWithNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for 'init_with' in parent_classes, expected to be of YAML type Scalar.";
   run_negative_integration_test("ParentClassesInitWithNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_PropertiesNotSequence_fixture)
{
   std::string expected_err = "unexpected type expecting YAML:: 3";
   run_negative_integration_test("PropertiesNotSequence", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_PropertiesSequenceElementNotMap_fixture)
{
   std::string expected_err = "Unexpected sequence element in \"properties\", expected to be of a YAML Map.";
   run_negative_integration_test("PropertiesSequenceElementNotMap", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_PropertiesMissingName_fixture)
{
   std::string expected_err = "Missing required key 'name' in properties.";
   run_negative_integration_test("PropertiesMissingName", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_PropertiesNameNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for 'name' in properties, expected to be of YAML type Scalar.";
   run_negative_integration_test("PropertiesNameNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ConstexprWithSetter_fixture)
{
   std::string expected_err = "Attribute property \"constexpr\" can not also exist when \"setter\"";
   run_negative_integration_test("ConstexprWithSetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ConstexprNotStatic_fixture)
{
   std::string expected_err = "Attribute property \"constexpr\" must also be \"static\".";
   run_negative_integration_test("ConstexprNotStatic", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ConstexprWithConstructorArg_fixture)
{
   std::string expected_err = "Attribute property \"constexpr\" can not be included with \"constructor_arg\".";
   run_negative_integration_test("ConstexprWithConstructorArg", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ConstexprWithGetterRef_fixture)
{
   std::string expected_err = "Attribute property \"constexpr\" can not be combined with \"getter_ref\".";
   run_negative_integration_test("ConstexprWithGetterRef", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ConstexprWithGetter_fixture)
{
   std::string expected_err = "Attribute property \"constexpr\" can not be combined with \"getter\".";
   run_negative_integration_test("ConstexprWithGetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_GetterAndExplicitGetter_fixture)
{
   std::string expected_err = "Attribute property cannot have both \"getter: true\" and \"explicit_getter: true\".";
   run_negative_integration_test("GetterAndExplicitGetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_SetterAndExplicitSetter_fixture)
{
   std::string expected_err = "Attribute property cannot have both \"setter: true\" and \"explicit_setter: true\".";
   run_negative_integration_test("SetterAndExplicitSetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_ExposedWithGetter_fixture)
{
   std::string expected_err = "Property attribute \"exposed\" can only be used when";
   run_negative_integration_test("ExposedWithGetter", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodParametersNotSequence_fixture)
{
   std::string expected_err = "unexpected type expecting YAML:: 3";
   run_negative_integration_test("MethodParametersNotSequence", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodsSequenceElementNotMap_fixture)
{
   std::string expected_err = "Unexpected sequence element in \"functions\", expected to be of a YAML Map.";
   run_negative_integration_test("MethodsSequenceElementNotMap", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodsMissingName_fixture)
{
   std::string expected_err = "Missing required key 'name' in methods.";
   run_negative_integration_test("MethodsMissingName", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodsNameNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for node 'name' in methods, expected to be of YAML type Scalar.";
   run_negative_integration_test("MethodsNameNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodsBodyNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for node 'body' in methods, expected to be of YAML type Scalar.";
   run_negative_integration_test("MethodsBodyNotScalar", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_MethodPrivateAndProtected_fixture)
{
   std::string expected_err = "Function properties \"private\" and \"protected\" cannot both be true.";
   run_negative_integration_test("MethodPrivateAndProtected", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_DependenciesSequenceElementNotMap_fixture)
{
   std::string expected_err = "Unexpected sequence element in \"dependencies\", expected to be of a YAML Map.";
   run_negative_integration_test("DependenciesSequenceElementNotMap", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_DependenciesMissingSymbol_fixture)
{
   std::string expected_err = "Missing required key 'symbol' in dependencies.";
   run_negative_integration_test("DependenciesMissingSymbol", expected_err);
}


TEST_F(Blast_Quintessence_YAMLParsers_QuintessenceParserTest,
   bin_program__fails_on_DependenciesSymbolNotScalar_fixture)
{
   std::string expected_err = "Unexpected type for 'symbol' in dependencies, expected to be of YAML type Scalar.";
   run_negative_integration_test("DependenciesSymbolNotScalar", expected_err);
}

