// #include <ncurses.h>
// #include <wchar.h>
// #include <curses.h>
// #include <ncurses.h>
// #include <wchar.h>
// #include <algorithm> 
// #include <cstring>
// #include <iostream>
// #include <locale>
// #include <string>
// #include <utility>
// #include <vector>

// #define CCHARW_MAX 5

// int main() {
//     // Initialize ncurses
//       std::locale::global(std::locale("en_US.UTF-8"));

//     initscr();
//     cbreak();
//     noecho();
//     keypad(stdscr, TRUE);
//       std::locale::global(std::locale("en_US.UTF-8"));


//     // Create a window
//     int height = 5;
//     int width = 20;
//     int starty = (LINES - height) / 2;    // Calculating for centering the window
//     int startx = (COLS - width) / 2;      // Calculating for centering the window
//     WINDOW *win = newwin(height, width, starty, startx);
//     refresh();

//     // Initialize boat
//     cchar_t boat;
//     boat.attr = A_NORMAL;
//     boat.chars[0] = L'🛥';

//     // Print boat on the window
//     mvwprintw(win, 1, 1, "%ls", boat.chars);
//     wrefresh(win);

//     // Wait for user input
//     getch();

//     // Clean up
//     delwin(win);
//     endwin();
//     return 0;
// }
