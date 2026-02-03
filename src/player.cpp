#include "../include/player.hpp"
#include "../include/boat.hpp"


void pickBoat(WINDOW* w, std::vector<std::pair<int,std::string>> boats) {
    auto ch = 0, cantBoats = static_cast<int>(boats.size());
    int horizontal = 0;
    int delta = 0;
    int pos = 0;

    init_pair(1, COLOR_RED, -1);

    keypad(w, TRUE);

    while ((ch = wgetch(w)) != '\n') {
        delta = 0;
        mvwaddch(w, 0, HEADER_COLS + horizontal * BOARD_COLS , 48 + horizontal);
        switch (ch) {
            case KEY_LEFT:
            case 'a':
            case 'A':
                delta = -1;
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                delta = 1;
                break;

            default:
                break;
        }

        horizontal = std::clamp(horizontal + delta, 0, cantBoats - 1);
        pos = HEADER_COLS + horizontal * BOARD_COLS;

        wattron(w, COLOR_PAIR(1));
        mvwaddch(w, 0, pos, 48 + horizontal);
        wattroff(w, COLOR_PAIR(1));

       // boatHighlighter(w, {2, pos}, boats[horizontal].first, {1, 0});
        wrefresh(w);
    }
}


void movePlayer(WINDOW* w) {
    int ch = 0, horizontal = 0, vertical = 0;
    int x = 0, y = 0;
    while ((ch = getch()) != 'q') {
        x = 0, y = 0;
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
        mvwaddstr(w, vertical * BOARD_ROWS, (horizontal * BOARD_COLS)-2, " . " );
        vertical   = std::clamp(vertical + y,   1, 10);
        horizontal = std::clamp(horizontal + x, 1, 10);
        mvwaddstr(w, vertical * BOARD_ROWS, (horizontal * BOARD_COLS)-2, "[.]" );
        wrefresh(w);
    }
}
