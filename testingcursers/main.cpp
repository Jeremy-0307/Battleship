// #include <iostream>
// #include <locale>
// #include <ncurses.h>
// #include <wchar.h>

// void print(WINDOW* w, int x, int y, cchar_t* wideChar, int n) {
//     for (int i = 0; i < n; ++i) {
//         mvwadd_wch(w, y, x + i, &wideChar[i]);
//     }
// }

// int main() {
//     initscr();
//     start_color(); 
//     use_default_colors();
//     std::locale::global(std::locale(""));

//     // Set the boat emoji
//     wchar_t boatEmoji = L'🛥';
//     cchar_t wideChar;
//     attr_t attributes = A_NORMAL;
//     setcchar(&wideChar, &boatEmoji, attributes, 0, NULL);

//     // Print boats across the screen
//     for (int x = 1; x < 20; x+=2) {
//         for (int y = 1; y < 10; ++y) {
//             print(stdscr, x, y, &wideChar, 1);
//         }
//     }
    
//     // Read a boat emoji from a specific position
//     cchar_t readChar;
//     mvwin_wch(stdscr, 6, 3, &readChar);
//     mvwadd_wch(stdscr, 14, 14, &readChar);

//     refresh();
//     getch();
//     endwin();

//     return 0;
// }
