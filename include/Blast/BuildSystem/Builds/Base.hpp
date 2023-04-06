#pragma once


#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <chrono>
#include <string>
#include <vector>


namespace Blast
{
   namespace BuildSystem
   {
      namespace Builds
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"Base";
            static constexpr char* STATUS_UNDEFINED = (char*)"undefined";
            static constexpr char* STATUS_WAITING_TO_START = (char*)"waiting_to_start";
            static constexpr char* STATUS_RUNNING = (char*)"running";
            static constexpr char* STATUS_FINISHED = (char*)"finished";
            static constexpr char* STATUS_ERROR = (char*)"error";

         private:
            std::string type;
            std::vector<Blast::BuildSystem::BuildStages::Base*> build_stages;
            std::chrono::high_resolution_clock::time_point started_at;
            std::chrono::high_resolution_clock::time_point ended_at;
            std::string status;

         protected:


         public:
            Base(std::string type=TYPE, std::vector<Blast::BuildSystem::BuildStages::Base*> build_stages={});
            ~Base();

            void set_build_stages(std::vector<Blast::BuildSystem::BuildStages::Base*> build_stages);
            void set_started_at(std::chrono::high_resolution_clock::time_point started_at);
            void set_ended_at(std::chrono::high_resolution_clock::time_point ended_at);
            void set_status(std::string status);
            std::string get_type() const;
            std::vector<Blast::BuildSystem::BuildStages::Base*> get_build_stages() const;
            std::chrono::high_resolution_clock::time_point get_started_at() const;
            std::chrono::high_resolution_clock::time_point get_ended_at() const;
            std::string get_status() const;
            bool is_type(std::string possible_type="");
            void run();
            static void build_stage_executor(Blast::BuildSystem::BuildStages::Base* build_stage=nullptr);
            void run_all_in_parallel();
            bool status_is(std::string possible_status=STATUS_UNDEFINED);
            bool finished_successfully();
            double infer_duration_seconds();
         };
      }
   }
}



