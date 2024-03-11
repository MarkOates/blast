#pragma once


#include <chrono>
#include <functional>
#include <mutex>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      namespace BuildStages
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"Base";
            static constexpr char* STATUS_WAITING_TO_START = (char*)"waiting_to_start";
            static constexpr char* STATUS_RUNNING = (char*)"running";
            static constexpr char* STATUS_SUCCEEDED = (char*)"succeeded";
            static constexpr char* STATUS_ERROR = (char*)"error";
            static constexpr char* STATUS_FAILED = (char*)"failed";

         private:
            std::string type;
            std::chrono::high_resolution_clock::time_point started_at;
            std::mutex mutex_for_started_at;
            std::chrono::high_resolution_clock::time_point ended_at;
            std::mutex mutex_for_ended_at;
            std::string status;
            int status_change_count;
            std::mutex mutex_for_status;
            std::function<void(std::string, std::chrono::high_resolution_clock::time_point, int)> on_status_change_callback;

         protected:


         public:
            Base(std::string type=TYPE);
            virtual ~Base();

            void set_on_status_change_callback(std::function<void(std::string, std::chrono::high_resolution_clock::time_point, int)> on_status_change_callback);
            std::string get_type() const;
            int get_status_change_count() const;
            std::function<void(std::string, std::chrono::high_resolution_clock::time_point, int)> get_on_status_change_callback() const;
            std::string get_status();
            void set_status(std::string status="[unset-status]");
            std::chrono::high_resolution_clock::time_point get_started_at();
            void set_started_at(std::chrono::high_resolution_clock::time_point started_at);
            std::chrono::high_resolution_clock::time_point get_ended_at();
            void set_ended_at(std::chrono::high_resolution_clock::time_point ended_at);
            bool is_type(std::string possible_type="");
            virtual bool execute();
            double calc_duration_seconds();
         };
      }
   }
}



