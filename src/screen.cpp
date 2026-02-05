#include "../include/screen.hpp"
#include <cstdio>

void highligher(WINDOW* w, char c, vector<xy> Coords, short color) {
    init_pair(1, color, -1);
    wattron(w, COLOR_PAIR(1));
    for (auto a: Coords) {
        mvwaddch(w, a.y, a.x, c);
    }
    wattroff(w, COLOR_PAIR(1));
}

WINDOW* initWin(int h, int w, int x, int y) {
    WINDOW* window = newwin(h, w, y, x);
    box(window, 0, 0);
    return window;
}

/******************** MAIN SCREEN ********************/

WINDOW* initBoard(const xy& origin) {
    WINDOW* w = initWin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        BOARD_SIZE * BOARD_COLS + 3,
        origin.x, origin.y
    );
    return w;
}

xy getBoardOrigin() {
    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);

    int total_cols = (BOARD_SIZE + 1) * BOARD_COLS;
    int total_rows = (BOARD_SIZE + 1) * BOARD_ROWS;

    int x = (max_x - total_cols) / 2;
    int y = (max_y - total_rows) / 2;

    return {x, y};
}

void drawBoard(WINDOW* w) {
    int x = 0, y = 0;
    for (int row = 0; row <= BOARD_SIZE; ++row) {
        for (int column = 0; column <= BOARD_SIZE; ++column) {
            x = 2 + (column - 1) * BOARD_COLS;
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

/******************** Boat SCREEN ********************/

WINDOW* initMenu(const xy& boardOrigin) {
    WINDOW* w = initWin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        (bWidth + (bQuant + 1) * 2),
        boardOrigin.x, boardOrigin.y);
    return w;
}

xy getMenuOrigin(const xy& boardOrigin) {
    int x = boardOrigin.x - (bWidth + (bQuant + 1) * 2);
    int y = boardOrigin.y;
    return {x, y};
}

void drawMenu(WINDOW* w) {
    int currbWidth = 0;

    for (std::size_t i = 0; i < boats.size(); ++i) {
        const auto& cells = boats[i].first;
        const chtype symbol = static_cast<chtype>(boats[i].second);

        auto [minX, maxX] = std::minmax_element(
            cells.begin(), cells.end(),
            [](const auto& a, const auto& c) {
                return a.x < c.x;
            }
        );
        currbWidth += 2;
        for (const auto& b : cells) {
            mvwaddch(w, 3 + b.y, currbWidth + b.x, symbol);
        }
        currbWidth += (maxX->x - minX->x) + 1;
    }
}


void initmenu() {
}
