

#include <Blast/BuildSystem/BuildStages/Base.hpp>




namespace Blast
{
namespace BuildSystem
{
namespace BuildStages
{


Base::Base(std::string type)
   : type(type)
   , started_at()
   , mutex_for_started_at()
   , ended_at()
   , mutex_for_ended_at()
   , status("[unset-status]")
   , status_change_count(0)
   , mutex_for_status()
   , on_status_change_callback({})
{
}


Base::~Base()
{
}


void Base::set_on_status_change_callback(std::function<void(std::string, std::chrono::high_resolution_clock::time_point, int)> on_status_change_callback)
{
   this->on_status_change_callback = on_status_change_callback;
}


std::string Base::get_type() const
{
   return type;
}


int Base::get_status_change_count() const
{
   return status_change_count;
}


std::function<void(std::string, std::chrono::high_resolution_clock::time_point, int)> Base::get_on_status_change_callback() const
{
   return on_status_change_callback;
}


std::string Base::get_status()
{
   std::string result;
   mutex_for_status.lock();
   result = status;
   mutex_for_status.unlock();
   return result;
}

void Base::set_status(std::string status)
{
   std::chrono::high_resolution_clock::time_point time_point = std::chrono::high_resolution_clock::now();

   mutex_for_status.lock();
   this->status = status;
   status_change_count++;
   mutex_for_status.unlock();

   // Because this callback occurs outside of the mutex in a threaded context, it's possible this callback
   // will occur out of synce from its order of execution. For this reason, the "status_change_count" var should
   // be used externally to ensure the latest status is used.
   if (on_status_change_callback) on_status_change_callback(status, time_point, status_change_count);

   return;
}

std::chrono::high_resolution_clock::time_point Base::get_started_at()
{
   std::chrono::high_resolution_clock::time_point result;
   mutex_for_started_at.lock();
   result = started_at;
   mutex_for_started_at.unlock();
   return result;
}

void Base::set_started_at(std::chrono::high_resolution_clock::time_point started_at)
{
   mutex_for_started_at.lock();
   this->started_at = started_at;
   mutex_for_started_at.unlock();
}

std::chrono::high_resolution_clock::time_point Base::get_ended_at()
{
   std::chrono::high_resolution_clock::time_point result;
   mutex_for_ended_at.lock();
   result = ended_at;
   mutex_for_ended_at.unlock();
   return result;
}

void Base::set_ended_at(std::chrono::high_resolution_clock::time_point ended_at)
{
   mutex_for_ended_at.lock();
   this->ended_at = ended_at;
   mutex_for_ended_at.unlock();
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

bool Base::execute()
{
   return true;
}

double Base::calc_duration_seconds()
{
   std::chrono::duration<double> elapsed_seconds = get_ended_at() - get_started_at();
   return elapsed_seconds.count();
}


} // namespace BuildStages
} // namespace BuildSystem
} // namespace Blast


