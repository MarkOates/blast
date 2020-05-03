#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile

#include <Blast/Project/ProjectSymlinkFixer.hpp>

int main(int argc, char **argv)
{
   Blast::Project::ProjectSymlinkFixer symlink_fixer;
   symlink_fixer.run();
   return 0;
}

