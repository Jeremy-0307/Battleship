#include "../include/screen.hpp"
#include <cstdio>

/******************** DRAW SCREEN ********************/

bool checkValid(WINDOW* w, const vector<xy>& pts, int limit) {
    for (const auto& p : pts) {
        if (p.x < 0 || p.x > limit || p.y < 0 || p.y > limit){
            return false;
        }
    }
    return true;
}

void draw(WINDOW* w, const vector<xy>& pts, const char* str, int colorID) {
    wattron(w, COLOR_PAIR(colorID));

    for (const auto& p : pts) {
        mvwaddstr(w, p.y, p.x, str);
    }

    wattroff(w, COLOR_PAIR(colorID));
}

int boatCoords(WINDOW* w, const xy& c) {
    for (int i = 0; i < bQuant; ++i) {
        for (const auto& p : boats[i].first) {
            if (p.x == c.x && p.y == c.y) {
                return i;
            }
        }
    }
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

vector<pair<vector<xy>,bool>> drawMenu(WINDOW* w) {
    int currbWidth = 0;
    vector<pair<vector<xy>, bool>> bMenu;

    for (std::size_t i = 0; i < bQuant; ++i) {
        const auto& bCoords = boats[i].first;

        auto [minX, maxX] = std::minmax_element(
            bCoords.begin(), bCoords.end(),
            [](const xy& a, const xy& c) {
                return a.x < c.x;
            }
        );

        currbWidth += 2;
        mvwaddch(w, 0, currbWidth + (maxX->x / 2), static_cast<chtype>('0' + i));

        vector<xy> bCurr;
        bCurr.reserve(bCoords.size());

        for (const auto& b : bCoords) {
            xy shifted{ b.x + currbWidth, b.y + 3 };
            bCurr.push_back(shifted);
            mvwaddstr(w, shifted.y, shifted.x, BCH);
        }

        bMenu.push_back({std::move(bCurr), true});
        currbWidth += (maxX->x - minX->x) + 1;
    }
    return bMenu;
}

void initmenu() {
}
