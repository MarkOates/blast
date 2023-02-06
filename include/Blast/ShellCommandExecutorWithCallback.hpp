#pragma once


#include <functional>
#include <string>


namespace Blast
{
   class ShellCommandExecutorWithCallback
   {
   private:
      std::string command;
      std::function<void(std::string)> callback;
      bool capture_stderr;
      bool executed_successfully;
      bool finished;

   protected:


   public:
      ShellCommandExecutorWithCallback(std::string command="echo hello!", std::function<void(std::string)> callback=ShellCommandExecutorWithCallback::simple_cout_callback, bool capture_stderr=true);
      ~ShellCommandExecutorWithCallback();

      void set_capture_stderr(bool capture_stderr);
      bool get_capture_stderr() const;
      bool get_executed_successfully() const;
      bool get_finished() const;
      static void simple_silent_callback(std::string string_for_appending="");
      static void simple_cout_callback(std::string string_for_appending="");
      std::string execute();
   };
}



