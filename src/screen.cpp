#include "../include/screen.hpp"

static std::string boat_board[BOARD_SIZE][BOARD_SIZE];
static std::string attack_board[BOARD_SIZE][BOARD_SIZE];

int max_x = 0, max_y = 0;

void highligher(WINDOW* w, char c, std::vector<pair<int, int>> Coords, short color) {
    init_pair(1, color, -1);
    wattron(w, COLOR_PAIR(1));
    for (auto a: Coords) {
        mvwaddch(w, a.second, a.first, c);
    }
    wattroff(w, COLOR_PAIR(1));
}

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

pair<int, int> setBoatMenuXY(const int bWidth, const int quantBoats, const pair<int, int>& boardXY) {

    int menuX = boardXY.first - (bWidth + (quantBoats + 1) * 2);
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

void drawBoatMenu(WINDOW* w, const vector<boat>& boats) {

    auto xWidthCounter = 0;
    auto x = 0;
    auto bWidth = 0;
    for(int i = 0; i < static_cast<int>(boats.size()); ++i) {
        auto [minX, maxX] = std::minmax_element(
            boats[i].first.begin(), boats[i].first.end(),
            [](const auto& a, const auto& c){ return a.first < c.first; }
        );

        xWidthCounter += 2;
        for(auto c : boats[i].first) {
            mvwaddch(w, 3 + c.second,  xWidthCounter + c.first, boats[i].second );
        }
        bWidth = (maxX->first - minX->first) + 1;
        xWidthCounter += bWidth;

        x = HEADER_COLS + bWidth * BOARD_COLS;

        mvwaddch(w, 0, x, '0' + static_cast<char>(i));
        mvwaddch(w, 1, x, 'v');

    }
}

void initmenu() {
}
