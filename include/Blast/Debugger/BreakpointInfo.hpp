#pragma once


#include <string>


namespace Blast
{
   namespace Debugger
   {
      class BreakpointInfo
      {
      private:
         std::string filename;
         int line;

      protected:


      public:
         BreakpointInfo(std::string filename="[unset-filename]", int line=0);
         ~BreakpointInfo();

         void set_filename(std::string filename);
         void set_line(int line);
         std::string get_filename() const;
         int get_line() const;
         std::string &get_filename_ref();
         int &get_line_ref();
      };
   }
}



