```
TEST_F(AllegroFlare_Screens_AchievementsTest, initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::Achievements achievements_screen;
   std::string expected_thrown_error_message =
      "Achievements::initialize: error: guard \"al_is_system_installed()\" not met";

   testing::internal::CaptureStdout();
   testing::internal::CaptureStderr();

   ASSERT_THROW_WITH_MESSAGE(achievements_screen.initialize(), std::runtime_error, expected_thrown_error_message);

   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   std::string actual_cerr_output = testing::internal::GetCapturedStderr();

   std::string expected_cerr_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Achievements::initialize", "al_is_system_installed()");
   std::string expected_cerr_output = expected_cerr_error_message;

   // TODO: replace below with something like "EXPECT_THAT(expected_cout_output.empty(), ::testing::IsEmpty());"
   EXPECT_EQ(true, actual_cout_output.empty()) << actual_cout_output;
   EXPECT_EQ(actual_cerr_output, expected_cerr_output) << actual_cerr_output;
}
```
