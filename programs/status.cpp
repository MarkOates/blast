
////#include <Projekt.h>









//#pragma once

//#include <ncurses_art/Element/ElementBase.hpp>
//#include <string>
//#include <vector>

//class AppController;

//class InjectedScene : public ElementBase
//{
//protected:
   //AppController *app_controller;
   //std::vector<ElementBase *> elements;

//public:
   //InjectedScene();
   //virtual ~InjectedScene();

   //void set_app_controller(AppController *app_controller);
   //bool emit_event(std::string event);
   //virtual bool process_input(char input_ch);
   //virtual bool process_event(std::string event);

   //std::vector<ElementBase *> &get_elements();

   //void draw() override;
//};










///////////////////////////////////////////////////////
//// #include <ncurses_art/AppController.hpp>
////////////////////////////////////////////////////

//#include <ncurses_art/EventQueue.hpp>
//#include <ncurses_art/Screen.hpp>

//class InjectedScene;

//class InjectedAppController
//{
//private:
   //static const int DEFAULT_USLEEP_DELAY;
   //bool initialized;
   //Screen screen;
   //EventQueue event_queue;
   //int usleep_delay;
   //bool program_aborted;
   //InjectedScene *Injectedscene;

//public:
   //InjectedAppController();
   //~InjectedAppController();

   //void initialize();
   //void set_scene(InjectedScene *Injectedscene);
   //void emit_event(std::string event);
   //void run_loop();
   //void validate_init();
   //void abort_program();
//};











//#include <ncurses_art/Element/InjectedScene.hpp>
//#include <ncurses_art/Element/Text.hpp>
//#include <ncurses_art/EventTypes.hpp>
//#include <ncurses_art/Screen.hpp>
//#include <ncurses.h>
//#include <stdexcept>
//#include <sstream>
//#include <unistd.h>

//#include <string>
//#include <fstream>
//#include <streambuf>

//const int InjectedAppController::DEFAULT_USLEEP_DELAY = 10000;

//InjectedAppController::InjectedAppController()
   //: initialized(false)
   //, screen()
   //, event_queue()
   //, usleep_delay(DEFAULT_USLEEP_DELAY)
   //, program_aborted(false)
   //, scene(nullptr)
//{
//}

//InjectedAppController::~InjectedAppController()
//{
//}

//void InjectedAppController::initialize()
//{
   //if (initialized) return;

   //screen.initialize();
   //initialized = true;
   //nodelay(stdscr, true);
   //emit_event(EVENT_PROGRAM_INITIALIZED);
//}

//void InjectedAppController::set_scene(Scene *scene)
//{
   //this->scene = scene;
//}

//void InjectedAppController::emit_event(std::string event)
//{
   //event_queue.append_event(event);
//}

//void InjectedAppController::run_loop()
//{
   //validate_init();

   //do
   //{
      //char ch = getch();
      //switch (ch)
      //{
      //case '\e':
         //emit_event(EVENT_ABORT_PROGRAM);
         //break;
      //case ERR:
         //break;
      //default:
         //if (scene) scene->process_input(ch);
         //break;
      //}

      //while (!event_queue.is_empty())
      //{
         //std::string event = event_queue.pop_event();

         //if (event == EVENT_ABORT_PROGRAM) abort_program();
         //else if (scene && scene->process_event(event)) break;
         //else throw std::runtime_error(std::string("unrecognized event ") + event);
      //}

      //if (scene) scene->draw();
      //else Text("- no scene is currently active -", COLS/2, LINES/3, 0.5).draw();

      //usleep(usleep_delay);
   //}
   //while (!program_aborted);
//}

//void InjectedAppController::validate_init()
//{
   //if (!initialized) throw std::runtime_error("InjectedAppController must be initialized before using functionality");
//}

//void InjectedAppController::abort_program()
//{
   //validate_init();
   //program_aborted = true;
//}












//#include <ncurses_art/Element/ElementBase.hpp>
//#include <ncurses_art/Element/Frame.hpp>
//#include <ncurses_art/Element/HeaderBar.hpp>
//#include <ncurses_art/Element/Menu.hpp>
//#include <ncurses_art/Element/ProgressBar.hpp>
//#include <ncurses_art/Element/Rectangle.hpp>
//#include <ncurses_art/Element/Scene.hpp>
//#include <ncurses_art/Element/Table.hpp>
//#include <ncurses_art/Element/TabSet.hpp>
//#include <ncurses_art/Element/Text.hpp>
//#include <ncurses_art/Element/TextInput.hpp>
//#include <ncurses_art/Element/WcharText.hpp>
//#include <ncurses_art/EventTypes.hpp>

//#include <allegro5/allegro.h>

//#define TMP_OUTFILE "/tmp/out.txt.tmp"

//std::vector<std::string> args;

//class Projekt : public Scene
//{
//public:
   //Projekt();
   //~Projekt();

   //bool process_input(char input_ch) override;
   //bool process_event(std::string event) override;
//};

//Projekt::~Projekt() {}

//int main(int argc, char **argv)
//{
   //for (int i=0; i<argc; i++) args.push_back(argv[i]);

   //InjectedAppController app_controller;
   //app_controller.initialize();
   //Projekt projekt;
   //projekt.set_app_controller(&app_controller);
   //app_controller.set_scene(&projekt);
   //app_controller.run_loop();
   //return 0;
//}






//#include <ncurses.h>

//#include <map>




//////////////////////////////////
//// #include "projekt_helper.h"
//////////////////////////////////


//#include <sstream>

//Projekt *current_project = nullptr;

//std::vector<Table *> tables()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve tables on a nullptr current_project");
   //std::vector<Table *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("Table")) results.push_back(static_cast<Table *>(element));
   //return results;
//}

//std::vector<TabSet *> tab_sets()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve tab_sets on a nullptr current_project");
   //std::vector<TabSet *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("TabSet")) results.push_back(static_cast<TabSet *>(element));
   //return results;
//}

//std::vector<Menu *> menus()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve menus on a nullptr current_project");
   //std::vector<Menu *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("Menu")) results.push_back(static_cast<Menu *>(element));
   //return results;
//}

//std::vector<Text *> texts()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve texts on a nullptr current_project");
   //std::vector<Text *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("Text")) results.push_back(static_cast<Text *>(element));
   //return results;
//}

//std::vector<WcharText *> wchar_texts()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve wchar_texts on a nullptr current_project");
   //std::vector<WcharText *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("WcharText")) results.push_back(static_cast<WcharText *>(element));
   //return results;
//}

//std::vector<TextInput *> text_inputs()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve text_inputs on a nullptr current_project");
   //std::vector<TextInput *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("TextInput")) results.push_back(static_cast<TextInput *>(element));
   //return results;
//}

//std::vector<Frame *> frames()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve frames on a nullptr current_project");
   //std::vector<Frame *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("Frame")) results.push_back(static_cast<Frame *>(element));
   //return results;
//}

//std::vector<ProgressBar *> progress_bars()
//{
   //if (!current_project) throw std::runtime_error("Cannot retrieve progress_bars on a nullptr current_project");
   //std::vector<ProgressBar *> results;
   //for (ElementBase *element : current_project->get_elements())
      //if (element->is_type("ProgressBar")) results.push_back(static_cast<ProgressBar *>(element));
   //return results;
//}

//TabSet &find_tab_set(std::string name)
//{
   //std::vector<TabSet *> results;
   //for (TabSet *tab_set : tab_sets()) if (tab_set->is_name(name)) return *tab_set;

   //std::stringstream error_message;
   //error_message << "Cannot find tab_set with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//Table &find_table(std::string name)
//{
   //std::vector<Table *> results;
   //for (Table *table : tables()) if (table->is_name(name)) return *table;

   //std::stringstream error_message;
   //error_message << "Cannot find table with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//Menu &find_menu(std::string name)
//{
   //std::vector<Menu *> results;
   //for (Menu *menu : menus()) if (menu->is_name(name)) return *menu;

   //std::stringstream error_message;
   //error_message << "Cannot find menu with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//Text &find_text(std::string name)
//{
   //std::vector<Text *> results;
   //for (Text *text : texts()) if (text->is_name(name)) return *text;

   //std::stringstream error_message;
   //error_message << "Cannot find text with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//WcharText &find_wchar_text(std::string name)
//{
   //std::vector<WcharText *> results;
   //for (WcharText *text : wchar_texts()) if (text->is_name(name)) return *text;

   //std::stringstream error_message;
   //error_message << "Cannot find wchar_text with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//TextInput &find_text_input(std::string name)
//{
   //std::vector<TextInput *> results;
   //for (TextInput *text_input : text_inputs()) if (text_input->is_name(name)) return *text_input;

   //std::stringstream error_message;
   //error_message << "Cannot find text_input with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//Frame &find_frame(std::string name)
//{
   //std::vector<Frame *> results;
   //for (Frame *frame : frames()) if (frame->is_name(name)) return *frame;

   //std::stringstream error_message;
   //error_message << "Cannot find frame with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//ProgressBar &find_progress_bar(std::string name)
//{
   //std::vector<ProgressBar *> results;
   //for (ProgressBar *progress_bar : progress_bars()) if (progress_bar->is_name(name)) return *progress_bar;

   //std::stringstream error_message;
   //error_message << "Cannot find progress_bar with the name \"" << name << "\"";
   //throw std::runtime_error(error_message.str());
//}

//Menu &last_menu()
//{
   //return (*menus().back());
//}

//ElementBase &last_element()
//{
   //if (!current_project) throw std::runtime_error("Cannot last_element on a nullptr current_project");
   //if (current_project->get_elements().empty()) throw std::runtime_error("Cannot retrieve last_element on an empty set of elements");
   //return *current_project->get_elements().back();
//}

//Table &create_table(std::string name="", int x=0, int y=0, std::vector<std::vector<std::string>> elements={})
//{
   //if (!current_project) throw std::runtime_error("Cannot create a table, current_project is not set");
   //Table *table = new Table(x, y, elements);
   //current_project->get_elements().push_back(table);
   //last_element().set_name(name);
   //return (*table);
//}

//Text &create_text(std::string name="", int x=0, int y=0, float align_x=0, float align_y=0)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a text, current_project is not set");
   //Text *text = new Text("", x, y, align_x, align_y);
   //current_project->get_elements().push_back(text);
   //last_element().set_name(name);
   //return (*text);
//}

//WcharText &create_wchar_text(std::string name="", int x=0, int y=0, float align_x=0)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a text, current_project is not set");
   //WcharText *text = new WcharText(L"", x, y, align_x);
   //current_project->get_elements().push_back(text);
   //last_element().set_name(name);
   //return (*text);
//}

//TextInput &create_text_input(std::string name="", int x=0, int y=0)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a text_input, current_project is not set");
   //TextInput *text_input = new TextInput(x, y);
   //current_project->get_elements().push_back(text_input);
   //last_element().set_name(name);
   //return (*text_input);
//}

//Menu &create_menu(std::string name="", float x=0, float y=0)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   //Menu *menu = new Menu(x, y, {});
   //current_project->get_elements().push_back(menu);
   //last_element().set_name(name);
   //return (*menu);
//}

//Frame &create_frame(std::string name="", int x=0, int y=0, int w=20, int h=6)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   //Frame *frame = new Frame(x, y, w, h);
   //current_project->get_elements().push_back(frame);
   //last_element().set_name(name);
   //return (*frame);
//}

//ProgressBar &create_progress_bar(std::string name="", int x=0, int y=0, int w=20, int h=6)
//{
   //if (!current_project) throw std::runtime_error("Cannot create a menu, current_project is not set");
   //ProgressBar *progress_bar = new ProgressBar(x, y, w, h);
   //current_project->get_elements().push_back(progress_bar);
   //last_element().set_name(name);
   //return (*progress_bar);
//}

//HeaderBar &create_header_bar(std::string name="")
//{
   //if (!current_project) throw std::runtime_error("Cannot create a header_bar, current_project is not set");
   //HeaderBar *header_bar = new HeaderBar();
   //current_project->get_elements().push_back(header_bar);
   //last_element().set_name(name);
   //return (*header_bar);
//}

//const std::string MOVE_CURSOR_DOWN = "move_cursor_down";
//const std::string MOVE_CURSOR_UP = "move_cursor_up";
//const std::string CHOOSE_CURRENT_MENU_ITEM = "choose_current_menu_item";

//void throwit(std::string message)
//{
   //throw std::runtime_error(message);
//}

//void emit_event(std::string event)
//{
   //if (!current_project)
   //{
      //std::stringstream ss;
      //ss << "Cannot emit_event " << event << ", current_project is not set";
      //throw std::runtime_error(ss.str());
   //}
   //current_project->emit_event(event);
//};

//// file content reader

//#include <fstream>
//#include <streambuf>

//std::string get_file_contents()
//{
   //std::ifstream t(TMP_OUTFILE);
   //std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   //return str;
//}

//// string tokenizer

//std::vector<std::string> split_string(std::string s, std::string delimiter)
//{
   //std::vector<std::string> results;

   //size_t pos = 0;
   //std::string token;
   //while ((pos = s.find(delimiter)) != std::string::npos) {
       //token = s.substr(0, pos);
       //results.push_back(token);
       //s.erase(0, pos + delimiter.length());
   //}
   //results.push_back(s);

   //return results;
//}

//// append new line to text

//bool append_text(Text &text, std::string str_to_append)
//{
   //std::string str = text.get_text();
   //str += str_to_append;
   //text.set_text(str);
   //return true;
//}










//Projekt::Projekt() { current_project = this; }

//std::map<char, std::string> mappings = {
   //{ 'q', EVENT_ABORT_PROGRAM },
//};

//void initialize();

//std::map<std::string, void(*)()> events = {
   //{ EVENT_PROGRAM_INITIALIZED, initialize },
//};

//bool Projekt::process_input(char input_ch)
//{
   //if (mappings.find(input_ch) == mappings.end()) return false;
   //return emit_event(mappings[input_ch]);
//}

//bool Projekt::process_event(std::string e)
//{
   //if (events.find(e) == events.end()) return false;
   //events[e]();
   //return true;
//}








/////////////////////////////////////////
//// original program:
////    ncurses_status_fetcher
/////////////////////////////////////////



#include <allegro5/allegro.h>
#include <map>




#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <HostnameExtractor.hpp>

#include <iostream>
#include <iomanip> // for std::setw and std::setfill
#include <algorithm> // for std::find

#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_ALL_STATUSES "REFRESH_ALL_STATUSES"
#define PROCESS_NEXT_STATUS "PROCESS_NEXT_STATUS"
#define REFRESH_OUTPUT_REPORT "REFRESH_OUTPUT_REPORT"
#define REFRESH_PROGRESS_BAR "REFRESH_PROGRESS_BAR"
#define INCREMENTAL_RUN "INCREMENTAL_RUN"

#define OUTPUT_REPORT_TEXT_IDENTIFIER "output report"
#define OUTPUT_REPORT_TEXT find_text(OUTPUT_REPORT_TEXT_IDENTIFIER)

#define HOSTNAME_TEXT_IDENTIFIER "hostname text"
#define HOSTNAME_TEXT find_text(HOSTNAME_TEXT_IDENTIFIER)

#define PROGRESS_BAR_IDENTIFIER "progress bar"
#define PROGRESS_BAR find_progress_bar(PROGRESS_BAR_IDENTIFIER)

#define PROGRESS_BAR_TEXT_IDENTIFIER "progress bar text"
#define PROGRESS_BAR_TEXT find_text(PROGRESS_BAR_TEXT_IDENTIFIER)

#define PROPERTY_DELIMITER ": "


using NcursesArt::GithubRepoStatusFetcher;


class ProjectStatus
{
private:
   std::string repo_name;

   bool exists_locally;
   bool in_sync;
   bool has_no_changed_files;
   bool has_no_untracked_files;
   bool has_no_staged_files;
   int num_local_branches;
   int num_remote_branches;

   GithubRepoStatusFetcher fetcher;

public:
   ProjectStatus(std::string repo_name)
      : repo_name(repo_name)
      , exists_locally(false)
      , in_sync(false)
      , has_no_changed_files(false)
      , has_no_untracked_files(false)
      , has_no_staged_files(false)
      , num_local_branches(0)
      , fetcher(repo_name)
   {}

   std::string get_repo_name()
   {
      return repo_name;
   }

   bool get_exists_locally()
   {
      return exists_locally;
   }

   bool get_in_sync()
   {
      return in_sync;
   }

   bool get_has_no_changed_files()
   {
      return has_no_changed_files;
   }

   bool get_has_no_untracked_files()
   {
      return has_no_untracked_files;
   }

   int get_num_local_branches()
   {
      return num_local_branches;
   }

   int get_num_remote_branches()
   {
      return num_remote_branches;
   }

   int get_has_no_staged_files()
   {
      return has_no_staged_files;
   }

   void process()
   {
      exists_locally = fetcher.local_repo_exists();
      in_sync = fetcher.is_the_repo_in_sync_with_remote();
      has_no_changed_files = !fetcher.has_file_changes();
      has_no_untracked_files = !fetcher.has_untracked_files();
      num_local_branches = fetcher.get_branch_count();
      has_no_staged_files = (fetcher.get_current_staged_files().size() == 0);
      num_remote_branches = fetcher.get_branch_count_at_remote();
   }
};


#include <sstream>

std::map<std::string, std::pair<bool, ProjectStatus>> projects = {};

std::string diamond_it(std::string label, int number)
{
   std::stringstream result;
   bool check = number == 1;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 ";
   else result << PROPERTY_DELIMITER << "🔸 ";
   result << number;

   return result.str();
}

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 yes";
   else result << PROPERTY_DELIMITER << "🔸 no";
   return result.str();
}

std::string show_it(std::string label, std::string value)
{
   std::stringstream result;
   result << label << PROPERTY_DELIMITER << value;
   return result.str();
}


#include <StringVectorIntersection.hpp>

//class Args
//{
//private:
   //std::vector<std::string> known_args;
   //std::vector<std::string> args;

   //bool find(std::string string)
   //{
      //return std::find(this->args.begin(), this->args.end(), string) != this->args.end();
   //}

//public:
   //Args()
      //: known_args({
         //"core",
         //"games",
        //})
      //, args{}
   //{}

   //void set(std::vector<std::string> args)
   //{
      //this->args = args;
   //}

   //void set(int argc, char **argv)
   //{
      //for (int i=0; i<argc; i++) this->args.push_back(argv[i]);
   //}

   //bool has(std::string arg_string_to_find)
   //{
      //return find(arg_string_to_find);
   //}

   //bool has_no_recognized_args()
   //{
      //StringVectorIntersection intersection(args, known_args);
      //return intersection.intersection().empty();
   //}
//};


enum final_status_t
{
   NONE = 0,
   UNPROCESSED,
   CLEAN,
   UNSYNCED,
   SOME_CLUTTERED_FILES,
   EXTRA_LOCAL_BRANCHES,
   //EXTRA_REMOTE_BRANCHES,
};


final_status_t get_final_status(int num_local_branches, bool project_has_been_processed, bool exists_locally, bool in_sync, bool has_no_changed_files, bool has_no_untracked_files, bool has_no_staged_files)
{
   if (project_has_been_processed == false) return UNPROCESSED;

   final_status_t status = CLEAN;
   if (num_local_branches > 1) status = EXTRA_LOCAL_BRANCHES;
   if (!exists_locally || !in_sync) status = UNSYNCED;
   if (!has_no_changed_files || !has_no_untracked_files || !has_no_staged_files) status = SOME_CLUTTERED_FILES;
   return status;
}


std::string get_hostname()
{
   return HostnameExtractor().get_computer_name();
}


std::string get_status_icon_and_text(final_status_t status, int num_local_branches, int num_remote_branches)
{
   switch (status)
   {
   case NONE:
      return "⧄  none";
      break;
   case UNPROCESSED:
      return "▫️  unprocessed";
      break;
   case CLEAN:
      return "💎 clean";
      break;
   case UNSYNCED:
      return "🔺 unsynced";
      break;
   case SOME_CLUTTERED_FILES:
      return "🔸 some cluttered files";
      break;
   case EXTRA_LOCAL_BRANCHES:
      return std::string("🔹 some extra local branches (") + std::to_string(num_local_branches) + ")";
      break;
   //case EXTRA_LOCAL_REMOTE_BRANCHES:
      //return std::string("🔹 some extra remote branches (") + std::to_string(num_remote_branches) + ")";
      //break;
   }

   return "🌌 status unknown";
}


bool have_all_projects_been_processed()
{
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (!project_has_been_processed) return false;
   }
   return true;
}


int get_number_of_projects_processed()
{
   int projects_processed_count = 0;
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (project_has_been_processed) projects_processed_count++;
   }
   return projects_processed_count;
}


//void initialize()
//{
   //events[INITIALIZE_SCENE] = []{
      ////create_text(HOSTNAME_TEXT_IDENTIFIER, 5, 2);
      ////create_progress_bar(PROGRESS_BAR_IDENTIFIER, 3, 2+2, 60, 3);
      ////create_text(PROGRESS_BAR_TEXT_IDENTIFIER, 5, 5+2);
      ////create_text(OUTPUT_REPORT_TEXT_IDENTIFIER, 3, 8+2);

      ////HOSTNAME_TEXT.set_text(get_hostname());

      ////PROGRESS_BAR_TEXT.set_text("processing...");

      ////Args magic_args;
      ////magic_args.set(args);

      //projects = {
         ////{ "Adventures of Beary",  { false, ProjectStatus("adventures-of-beary") } },
         ////{ "Alex Park",            { false, ProjectStatus("AlexPark") } },
         ////{ "HomeServer",       { false, ProjectStatus("HomeServer") } },
         //{ "LabyrinthOfLore",  { false, ProjectStatus("LabyrinthOfLore") } },
         ////{ "Peri",      { false, ProjectStatus("Peri") } },
         //{ "Solitare",          { false, ProjectStatus("Solitare") } },
         ////{ "allegro-planet",   { false, ProjectStatus("allegro-planet") } },
         ////{ "allegroflare.github.io", { false, ProjectStatus("allegroflare.github.io") } },
         ////{ "beary2d",              { false, ProjectStatus("beary2d") } },
         ////{ "crayola",          { false, ProjectStatus("crayola") } },
         ////{ "crayola-client",   { false, ProjectStatus("crayola-client") } },
         ////{ "disclife",         { false, ProjectStatus("disclife") } },
         ////{ "dungeon",              { false, ProjectStatus("dungeon") } },
         //{ "first_vim_plugin", { false, ProjectStatus("first_vim_plugin") } },
         ////{ "flare_network",    { false, ProjectStatus("flare_network") } },
         //{ "fullscore",        { false, ProjectStatus("fullscore") } },
         //{ "motris",               { false, ProjectStatus("motris") } },
         ////{ "tilemap",              { false, ProjectStatus("tilemap") } },
         //{ "Fade to White (Krampus21)", { false, ProjectStatus("Krampus21") } },
         //{ ".dotfiles",        { false, ProjectStatus(".dotfiles") } },
         //{ "DragonWrath",      { false, ProjectStatus("DragonWrath") } },
         //{ "ChatGPT",      { false, ProjectStatus("ChatGPT") } },
         //{ "KrampusReturns",      { false, ProjectStatus("KrampusReturns") } },
         //{ "Releaser",      { false, ProjectStatus("Releaser") } },
         //{ "Slug3D",               { false, ProjectStatus("slug_3d") } },
         //{ "allegro_flare",    { false, ProjectStatus("allegro_flare") } },
         //{ "beebot",           { false, ProjectStatus("beebot") } },
         //{ "blast",            { false, ProjectStatus("blast") } },
         //{ "dungeon",            { false, ProjectStatus("dungeon") } },
         //{ "hexagon",          { false, ProjectStatus("hexagon") } },
         //{ "lightracer-max",       { false, ProjectStatus("lightracer-max") } },
         //{ "me",               { false, ProjectStatus("me") } },
         ////{ "ncurses-art",      { false, ProjectStatus("ncurses-art") } },
         //{ "oatescodes",       { false, ProjectStatus("oatescodes") } },
         ////{ "tileo",                { false, ProjectStatus("tileo") } },
         //{ "union",            { false, ProjectStatus("union") } },
         ////{ "Wicked",            { false, ProjectStatus("Wicked") } },
         ////{ "/Library/Application Support/Adobe/CEP/extensions", { false, ProjectStatus("unset") } },
      //};

      //emit_event(REFRESH_OUTPUT_REPORT);
      //emit_event(REFRESH_PROGRESS_BAR);
   //};
   //events[PROCESS_NEXT_STATUS] = []{
      //if (projects.empty()) return;

      //for (auto &project : projects)
      //{
         //bool project_has_been_processed = project.second.first;
         //if (!project_has_been_processed)
         //{
            //std::string project_identifier = project.first;
            //ProjectStatus &project_status = project.second.second;
            //bool &project_processed_state = project.second.first;

            //project_status.process();
            //project_processed_state = true;

            //break;
         //}
      //}
   //};
   //events[INCREMENTAL_RUN] = []{
      //if (!have_all_projects_been_processed())
      //{
         //emit_event(PROCESS_NEXT_STATUS);
         //emit_event(REFRESH_OUTPUT_REPORT);
         //emit_event(REFRESH_PROGRESS_BAR);
         //emit_event(INCREMENTAL_RUN);
      //}
      //else
      //{
         //PROGRESS_BAR_TEXT.set_text("finished.");
      //}
   //};
   //events[REFRESH_PROGRESS_BAR] = []{
      //int total_number_of_projects_for_processing = projects.size();
      //int number_of_projects_processed = get_number_of_projects_processed();
      //float updated_progress_bar_value = (float)number_of_projects_processed / total_number_of_projects_for_processing;
      //PROGRESS_BAR.set_value(updated_progress_bar_value);
   //};
   //events[REFRESH_OUTPUT_REPORT] = []{
      //std::stringstream result_text;

      //result_text << "[i] This tool does not check the status of *branches* within the repos" << std::endl << std::endl << std::endl;
      //result_text << "[i] This tool does check if there are extra remote branches, but will not include it in the final evaluation." << std::endl << std::endl << std::endl;

      //for (auto &project : projects)
      //{
         //ProjectStatus &project_status = project.second.second;
         //bool exists_locally = project_status.get_exists_locally();
         //bool in_sync = project_status.get_in_sync();
         //bool has_no_changed_files = project_status.get_has_no_changed_files();
         //bool has_no_untracked_files = project_status.get_has_no_untracked_files();
         //bool has_no_staged_files = project_status.get_has_no_staged_files();
         //int num_local_branches = project_status.get_num_local_branches();
         //int num_remote_branches = project_status.get_num_remote_branches();
         //std::string project_identifier = project.first;
         //std::string repo_name = project_status.get_repo_name();
         //bool project_has_been_processed = project.second.first;
         //final_status_t final_status = get_final_status(num_local_branches, project_has_been_processed, exists_locally, in_sync, has_no_changed_files, has_no_untracked_files, has_no_staged_files);

         //int longest_project_name_length = 24;
         //int project_name_right_padding = 3;
         ////std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-');
         //std::string status_icon_and_text = get_status_icon_and_text(final_status, num_local_branches, num_remote_branches);
         //result_text
            //<< std::left << std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-') << (project_identifier + " ")
            //<< status_icon_and_text;
         //if (project_has_been_processed == true && !(final_status == CLEAN || final_status == EXTRA_LOCAL_BRANCHES))
         //{

            //result_text << std::endl;
            //result_text << std::endl;
            ////result_text << "  " << show_it("repo name", repo_name) << std::endl;
            //result_text << "  " << check_it("repo exists locally", exists_locally) << std::endl;
            //result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
            //result_text << "  " << diamond_it("num remote branches", num_remote_branches) << std::endl;
            //result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
            //result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
            //result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
            //result_text << "  " << check_it("has no staged files", has_no_staged_files) << std::endl;
         //}
         //result_text << std::endl;
      //}

      ////result_text << std::endl << "some processing messaging garbage:" << std::endl << std::endl << std::endl;

      //OUTPUT_REPORT_TEXT.set_text(result_text.str());
   //};
   //events[REFRESH_ALL_STATUSES] = []{
      //for (auto &project : projects)
      //{
         //std::string project_identifier = project.first;
         //ProjectStatus &project_status = project.second.second;
         //bool &project_processed_state = project.second.first;

         //std::cout << "processing \"" << project_identifier << "\"" << std::endl;
         //project_status.process();
         //project_processed_state = true;
      //}

      //PROGRESS_BAR_TEXT.set_text("finished.");
   //};

   //emit_event(INITIALIZE_SCENE);
   //emit_event(INCREMENTAL_RUN);
//}






std::string create_output_report()
{
   std::stringstream result_text;

   result_text << "[i] This tool does not check the status of *branches* within the repos" << std::endl << std::endl << std::endl;
   result_text << "[i] This tool does check if there are extra remote branches, but will not include it in the final evaluation." << std::endl << std::endl << std::endl;

   for (auto &project : projects)
   {
      ProjectStatus &project_status = project.second.second;
      bool exists_locally = project_status.get_exists_locally();
      bool in_sync = project_status.get_in_sync();
      bool has_no_changed_files = project_status.get_has_no_changed_files();
      bool has_no_untracked_files = project_status.get_has_no_untracked_files();
      bool has_no_staged_files = project_status.get_has_no_staged_files();
      int num_local_branches = project_status.get_num_local_branches();
      int num_remote_branches = project_status.get_num_remote_branches();
      std::string project_identifier = project.first;
      std::string repo_name = project_status.get_repo_name();
      bool project_has_been_processed = project.second.first;
      final_status_t final_status = get_final_status(num_local_branches, project_has_been_processed, exists_locally, in_sync, has_no_changed_files, has_no_untracked_files, has_no_staged_files);

      int longest_project_name_length = 24;
      int project_name_right_padding = 3;
      //std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-');
      std::string status_icon_and_text = get_status_icon_and_text(final_status, num_local_branches, num_remote_branches);
      result_text
         << std::left << std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-') << (project_identifier + " ")
         << status_icon_and_text;
      if (project_has_been_processed == true && !(final_status == CLEAN || final_status == EXTRA_LOCAL_BRANCHES))
      {

         result_text << std::endl;
         result_text << std::endl;
         //result_text << "  " << show_it("repo name", repo_name) << std::endl;
         result_text << "  " << check_it("repo exists locally", exists_locally) << std::endl;
         result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
         result_text << "  " << diamond_it("num remote branches", num_remote_branches) << std::endl;
         result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
         result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
         result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
         result_text << "  " << check_it("has no staged files", has_no_staged_files) << std::endl;
      }
      result_text << std::endl;
   }

   //result_text << std::endl << "some processing messaging garbage:" << std::endl << std::endl << std::endl;

   //OUTPUT_REPORT_TEXT.set_text(result_text.str());
   return result_text.str();
}





//std::map<std::string, std::pair<bool, ProjectStatus>> projects = {};


int main(int argc, char **argv)
{
   projects = {
      //{ "Adventures of Beary",  { false, ProjectStatus("adventures-of-beary") } },
      //{ "Alex Park",            { false, ProjectStatus("AlexPark") } },
      //{ "HomeServer",       { false, ProjectStatus("HomeServer") } },
      { "LabyrinthOfLore",  { false, ProjectStatus("LabyrinthOfLore") } },
      //{ "Peri",      { false, ProjectStatus("Peri") } },
      { "Solitare",          { false, ProjectStatus("Solitare") } },
      //{ "allegro-planet",   { false, ProjectStatus("allegro-planet") } },
      //{ "allegroflare.github.io", { false, ProjectStatus("allegroflare.github.io") } },
      //{ "beary2d",              { false, ProjectStatus("beary2d") } },
      //{ "crayola",          { false, ProjectStatus("crayola") } },
      //{ "crayola-client",   { false, ProjectStatus("crayola-client") } },
      //{ "disclife",         { false, ProjectStatus("disclife") } },
      //{ "dungeon",              { false, ProjectStatus("dungeon") } },
      { "first_vim_plugin", { false, ProjectStatus("first_vim_plugin") } },
      //{ "flare_network",    { false, ProjectStatus("flare_network") } },
      { "fullscore",        { false, ProjectStatus("fullscore") } },
      { "motris",               { false, ProjectStatus("motris") } },
      //{ "tilemap",              { false, ProjectStatus("tilemap") } },
      { "Fade to White (Krampus21)", { false, ProjectStatus("Krampus21") } },
      { ".dotfiles",        { false, ProjectStatus(".dotfiles") } },
      { "DragonWrath",      { false, ProjectStatus("DragonWrath") } },
      { "ChatGPT",      { false, ProjectStatus("ChatGPT") } },
      { "KrampusReturns",      { false, ProjectStatus("KrampusReturns") } },
      { "Releaser",      { false, ProjectStatus("Releaser") } },
      { "Slug3D",               { false, ProjectStatus("slug_3d") } },
      { "allegro_flare",    { false, ProjectStatus("allegro_flare") } },
      { "beebot",           { false, ProjectStatus("beebot") } },
      { "blast",            { false, ProjectStatus("blast") } },
      { "dungeon",            { false, ProjectStatus("dungeon") } },
      { "hexagon",          { false, ProjectStatus("hexagon") } },
      { "lightracer-max",       { false, ProjectStatus("lightracer-max") } },
      { "me",               { false, ProjectStatus("me") } },
      //{ "ncurses-art",      { false, ProjectStatus("ncurses-art") } },
      { "oatescodes",       { false, ProjectStatus("oatescodes") } },
      //{ "tileo",                { false, ProjectStatus("tileo") } },
      { "union",            { false, ProjectStatus("union") } },
      //{ "Wicked",            { false, ProjectStatus("Wicked") } },
      //{ "/Library/Application Support/Adobe/CEP/extensions", { false, ProjectStatus("unset") } },
   };


   //if (projects.empty()) return;

   int project_count = projects.size();
   int projects_processed = 0;

   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (!project_has_been_processed)
      {
         std::string project_identifier = project.first;
         ProjectStatus &project_status = project.second.second;
         bool &project_processed_state = project.second.first;

         std::cout << "processing " << projects_processed << " of " << project_count << ": " << project_identifier << std::endl;
         project_status.process();
         std::cout << "processed " << project_identifier << " successfully." << std::endl;
         project_processed_state = true;
         projects_processed++;




         //std::cout << "  report:" << std::endl;
         std::cout << std::endl;
      }
   }


   std::cout << create_output_report() << std::endl;



   return 0;
}



