#include "../include/player.hpp"

void movePlayer(WINDOW* w) {
    int ch = 0, horizontal = 0, vertical = 0;
    int x = 0, y = 0;
    while ((ch = getch()) != 'q') {
        int x = 0, y = 0;
        switch (ch) {
            case KEY_UP:
            case 'w':
                y--;
                break;
            case KEY_DOWN:
            case 's':
                y++;
                break;
            case KEY_LEFT:
            case 'a':
                x--;
                break;
            case KEY_RIGHT:
            case 'd':
                x++;
                break;
            default:
                break;
        }
        mvwaddstr(w, vertical * BOARD_ROWS, (horizontal * BOARD_COLS)-1, " . " );
        vertical   = std::clamp(vertical+y,   1, 10);
        horizontal = std::clamp(horizontal+x, 1, 10);
        mvwaddstr(w, vertical * BOARD_ROWS, (horizontal * BOARD_COLS)-1, "[.]" );
        wrefresh(w);
    }
}
