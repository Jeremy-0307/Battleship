#include <string>
#include <utility>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#include "../include/screen.hpp"
#include "../include/player.hpp"
#include "../include/boat.hpp"

/*
* Empiezan de 0,0 > abajo derecha
* 0    0    0
* 0    0   000
* 0    0  0   0
* 0  000
*/

vector<boat> boats = {
    // el primer XY es el
    { {{0,2},{0,1},{0,0},{0,3},{0,4}},      'o'},
    { {{2,2},{2,1},{2,0},{2,3},{1,3},{0,3}},'o'},
    { {{2,1},{2,0},{1,1},{3,1},{0,2},{4,2}},'o'}
};

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(0);
    refresh();

    const pair<int, int> boardXY = setBoardXY();
    WINDOW* boardWin = initNewin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        BOARD_SIZE * BOARD_COLS + 3,
        boardXY.first, boardXY.second);

    auto bWidth = 0;
    for(auto b: boats){
        auto [minX, maxX] = std::minmax_element(
            b.first.begin(), b.first.end(),
            [](const auto& a, const auto& c){ return a.first < c.first; }
        );
        bWidth += (maxX->first - minX->first) + 1;
    }

    int quantBoats = static_cast<int>(boats.size());



    pair<int, int> boatMenuXY = setBoatMenuXY(bWidth, quantBoats, boardXY);
    WINDOW* boatMenuWin = initNewin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        bWidth + static_cast<int>(boats.size() + 1) * 2,
        boatMenuXY.first, boatMenuXY.second);

    wrefresh(boardWin);
    drawBoard(boardWin);
    drawBoatMenu(boatMenuWin, boats);

    wrefresh(boardWin);
    wrefresh(boatMenuWin);

    while(wgetch(boardWin) != 'q');
    //pickBoat(boatMenuWin, boats);

    delwin(boardWin);
    delwin(boatMenuWin);
    endwin();

    return 0;
}
