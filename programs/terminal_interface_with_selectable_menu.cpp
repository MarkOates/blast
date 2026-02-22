#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <allegro5/allegro.h> // Included per requirement

// ANSI Escape Codes
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define BG_CYAN     "\033[46m"
#define FG_BLACK    "\033[30m"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define MOVE_UP(x)  "\033[" << x << "A" // Moves cursor up x lines

char getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}

void renderMenu(const std::vector<std::string>& options, int selected, bool firstRender) {
    // If it's not the first time, move the cursor back up to the top of the menu
    if (!firstRender) {
        // We move up (number of options + 2) to account for header and spacing
        std::cout << MOVE_UP(options.size() + 2);
    }

    std::cout << BOLD << "--- Use J/K or Arrows to Navigate ---" << RESET << "\n\n";

    for (int i = 0; i < options.size(); ++i) {
        // Clear current line before printing to prevent ghost characters
        std::cout << "\33[2K\r"; 
        
        if (i == selected) {
            std::cout << BG_CYAN << FG_BLACK << "> " << options[i] << "  " << RESET << "\n";
        } else {
            std::cout << "  " << options[i] << "\n";
        }
    }
    std::cout.flush();
}

int main(int argc, char* argv[]) {
    // Allegro initialization (just to ensure the header is functional)
    // Note: al_init() isn't strictly needed for terminal IO, but satisfies the dependency.
    al_init(); 

    std::vector<std::string> options = {
        "Start New Game",
        "Load Save File",
        "Settings",
        "Exit Program"
    };

    int selected = 0;
    bool running = true;
    bool firstRender = true;

    std::cout << HIDE_CURSOR;

    while (running) {
        renderMenu(options, selected, firstRender);
        firstRender = false;

        char c = getch();

        if (c == 'k' || c == 'K') {
            selected = (selected - 1 + (int)options.size()) % (int)options.size();
        } 
        else if (c == 'j' || c == 'J') {
            selected = (selected + 1) % (int)options.size();
        } 
        else if (c == '\n') {
            running = false; 
        } 
        else if (c == '\033') { // Handle arrow keys
            if (getch() == '[') {
                switch(getch()) {
                    case 'A': selected = (selected - 1 + (int)options.size()) % (int)options.size(); break;
                    case 'B': selected = (selected + 1) % (int)options.size(); break;
                }
            }
        }
    }

    std::cout << SHOW_CURSOR << "\nSelection Confirmed: " << BOLD << options[selected] << RESET << "\n";

    return 0;
}
