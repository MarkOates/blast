

#include <Blast/BuildSystem/Builds/Base.hpp>

#include <iostream>
#include <thread>


namespace Blast
{
namespace BuildSystem
{
namespace Builds
{


Base::Base(std::string type, std::vector<Blast::BuildSystem::BuildStages::Base*> build_stages)
   : type(type)
   , build_stages(build_stages)
   , started_at()
   , ended_at()
   , status(STATUS_WAITING_TO_START)
{
}


Base::~Base()
{
}


void Base::set_build_stages(std::vector<Blast::BuildSystem::BuildStages::Base*> build_stages)
{
   this->build_stages = build_stages;
}


void Base::set_started_at(std::chrono::high_resolution_clock::time_point started_at)
{
   this->started_at = started_at;
}


void Base::set_ended_at(std::chrono::high_resolution_clock::time_point ended_at)
{
   this->ended_at = ended_at;
}


void Base::set_status(std::string status)
{
   this->status = status;
}


std::string Base::get_type() const
{
   return type;
}


std::vector<Blast::BuildSystem::BuildStages::Base*> Base::get_build_stages() const
{
   return build_stages;
}


std::chrono::high_resolution_clock::time_point Base::get_started_at() const
{
   return started_at;
}


std::chrono::high_resolution_clock::time_point Base::get_ended_at() const
{
   return ended_at;
}


std::string Base::get_status() const
{
   return status;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

void Base::run()
{
   started_at = std::chrono::high_resolution_clock::now();
   status = STATUS_RUNNING;

   // set all the statuses to STATUS_NOT_STARTED
   for (auto &build_stage : build_stages)
   {
      build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_WAITING_TO_START);
   }

   // run the stages one-by-one, or halt when one fails
   for (auto &build_stage : build_stages)
   {
      build_stage->set_started_at(std::chrono::high_resolution_clock::now());
      build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_RUNNING);
      try
      {
         bool executed_without_failure = build_stage->execute();
         if (executed_without_failure)
         {
            build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_SUCCEEDED);
         }
         else
         {
            build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_FAILED);
            status = STATUS_ERROR;
         }
      }
      catch (const std::exception& e)
      {
         std::cout << "There was an error during the execution of build stage. The following error message was "
               "thrown:" << std::endl;
         std::cout << e.what() << std::endl;
         build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_ERROR);
         status = STATUS_ERROR;
      }
      build_stage->set_ended_at(std::chrono::high_resolution_clock::now());

      if (status == STATUS_ERROR)
      {
         ended_at = std::chrono::high_resolution_clock::now();
         return;
      }
   }

   // set the status to STATUS_FINISHED when all the stages are completed (without error)
   status = STATUS_FINISHED;
   ended_at = std::chrono::high_resolution_clock::now();
   return;
}

void Base::build_stage_executor(Blast::BuildSystem::BuildStages::Base* build_stage)
{
   build_stage->set_started_at(std::chrono::high_resolution_clock::now());
   build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_RUNNING);
   try
   {
      bool executed_without_failure = build_stage->execute();
      if (executed_without_failure)
      {
         build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_SUCCEEDED);
      }
      else
      {
         build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_FAILED);
      }
   }
   catch (const std::exception& e)
   {
      std::cout << "There was an error during the execution of build stage. The following error message was "
            "thrown:" << std::endl;
      std::cout << e.what() << std::endl;
      build_stage->set_status(Blast::BuildSystem::BuildStages::Base::STATUS_ERROR);
   }
   build_stage->set_ended_at(std::chrono::high_resolution_clock::now());
   return;
}

void Base::run_all_in_parallel()
{
   started_at = std::chrono::high_resolution_clock::now();

   // set statuses of all stages to WAITING_TO_START

   // TODO: work out a nice way for the build_stages to be validated and distributed across threads
   // Right now, this funtion is hard-coded to build exactly 3 build stages in parallel.
   std::thread thread1(build_stage_executor, build_stages[0]);
   std::thread thread2(build_stage_executor, build_stages[1]);
   std::thread thread3(build_stage_executor, build_stages[2]);

   thread1.join();
   thread2.join();
   thread3.join();

   //TODO: check for error status

   status = STATUS_FINISHED;
   ended_at = std::chrono::high_resolution_clock::now();
   return;
}

bool Base::status_is(std::string possible_status)
{
   return possible_status == get_status();
}

bool Base::finished_successfully()
{
   return status == STATUS_FINISHED;
}

double Base::infer_duration_seconds()
{
   std::chrono::duration<double> elapsed_seconds = ended_at - started_at;
   return elapsed_seconds.count();
}


} // namespace Builds
} // namespace BuildSystem
} // namespace Blast


