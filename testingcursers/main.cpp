// #include <ncurses.h>

// int main() {
//     // Initialize ncurses
//     initscr();
//     cbreak();
//     noecho();

//     // Check for color support
//     if (!has_colors()) {
//         printw("Your terminal does not support color.\n");
//         endwin();
//         return 1;
//     }

//     // Enable color mode
//     start_color();

//     // Create a window
//     WINDOW *win = newwin(10, 20, 5, 5);
//     box(win, 0, 0); // Draw a border around the window
//     wrefresh(win);

//     // Set up some color pairs
//     init_pair(1, COLOR_RED, COLOR_GREEN); // Example color pair

//     // Set the background color at a specific position
//     wbkgd(win, COLOR_PAIR(1)); // Set the background color of the window to
//     the example color pair

//     // Refresh the window to show the background color
//     wrefresh(win);

//     // Get the background color of a character at a specific position
//     attron(COLOR_PAIR(1));
//     int x = 2;
//     int y = 2;
//     chtype ch = mvwinch(win, y, x);
//     int color_pair = PAIR_NUMBER(ch & A_COLOR); // Extract color pair number
//     from attributes short fg_color, bg_color; pair_content(color_pair,
//     &fg_color, &bg_color); // Get foreground and background color numbers
//     init_pair(2, bg_color, fg_color);
//     printw("Background color at position (%d, %d):\n", x, y);
//     attroff(COLOR_PAIR(1));
//     attron(COLOR_PAIR(2));
//     printw("Color pair number: %d\n", color_pair);
//     printw("Background color number: %d\n", bg_color);
//     printw("Foreground color number: %d\n", fg_color);
//     attroff(COLOR_PAIR(2));

//     // Refresh the standard screen to show the output
//     refresh();

//     // Wait for a key press before exiting
//     getch();

//     // Clean up
//     delwin(win);
//     endwin();

//     return 0;
// }
