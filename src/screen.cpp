#include "../include/screen.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

static std::string boat_board[BOARD_SIZE][BOARD_SIZE];
static std::string attack_board[BOARD_SIZE][BOARD_SIZE];

int max_x = 0, max_y = 0;

WINDOW* initNewin(int h, int w, int startX, int startY) {
    WINDOW* window = newwin(h, w, startY, startX);
    box(window, 0, 0);
    wrefresh(window);
    return window;
}

pair<int, int> setBoardXY() {
    getmaxyx(stdscr, max_y, max_x);

    int total_cols = (BOARD_SIZE + 1) * BOARD_COLS;
    int total_rows = (BOARD_SIZE + 1) * BOARD_ROWS;

    int initX = (max_x - total_cols) / 2;
    int initY = (max_y - total_rows) / 2;

    return {initX, initY};
}

pair<int, int> setMenuXY(const BoatList& boats) {
    int biggestBoat = 0;
    int quantBoats = static_cast<int>(boats.size());
    for (int i = 0; i < quantBoats; ++i) {
        biggestBoat = (biggestBoat <= boats[i].first) ? boats[i].first : biggestBoat;
    }

    int total_cols = quantBoats + (quantBoats + 1) * 2 + 2;
    int total_rows = biggestBoat + 4;

    int initX = (max_x - total_cols) / 2;
    int initY = (max_y - total_rows) / 2;

    return {initX, initY};
}

void drawBoard(WINDOW* w,const int initX, const int initY) {
    for (int column = 0; column <= BOARD_SIZE; ++column) {
        for (int row = 0; row <= BOARD_SIZE; ++row) {
            if (row == 0 && column >= 1) {
                mvwaddch(w, column * BOARD_ROWS, row, '0' + (column - 1));
            }
            else if (column == 0 && row >= 1) {
                mvwaddch(w, column, row * BOARD_COLS, 'A' + (row - 1));
            }
            else if (column != 0 && row != 0) {
                 mvwaddch(w, column * BOARD_ROWS, row * BOARD_COLS, '.');
            }
        }
        printw("\n");
    }
}

void initmenu() {
}
