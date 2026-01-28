#include "../include/screen.hpp"

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

pair<int, int> setBoatMenuXY(const BoatList& boats, const pair<int, int>& boardXY) {
    int quantBoats = static_cast<int>(boats.size());
    int menuX = boardXY.first - (quantBoats + 1) * BOARD_COLS;
    int menuY = boardXY.second;
    return {menuX, menuY};
}

void drawBoard(WINDOW* w) {
    int x = 0, y = 0;
    for (int row = 0; row <= BOARD_SIZE; ++row) {
        for (int column = 0; column <= BOARD_SIZE; ++column) {
            x = HEADER_COLS + (column - 1) * BOARD_COLS;
            y = BOARD_ROWS + (row - 1) * BOARD_ROWS;

            if (column == 0 && row >= 1) {
                mvwaddch(w, y, 0, 47 + row);
            }
            else if (row == 0 && column >= 1) {
                mvwaddch(w, 0, x, 64 + column);
            }
            else if (row != 0 && column != 0) {
                mvwaddch(w, y, x, '.');
            }
        }
    }
}

void drawBoatMenu(WINDOW* w, const BoatList& boats) {
    const int bSize = boats.size();

    for (int column = 0; column < bSize; ++column) {
        int x = HEADER_COLS + column * BOARD_COLS;

        mvwaddch(w, 0, x, '0' + column);
        mvwaddch(w, 1, x, 'v');

        int sizeBoat = boats[column].first + 3;

        for (int y = 3; y <= sizeBoat; ++y) {
            mvwaddch(w, y, x, 'O');
        }
    }
}



void initmenu() {
}
