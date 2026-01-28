#include <string>
#include <utility>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#include "../include/screen.hpp"
#include "../include/player.hpp"


using std::pair;
using BoatList = std::vector<std::pair<int, std::string>>;
BoatList boats = {
    {4, "4"},
    {3, "3"},
    {3, "2"},
    {1, "1"},
};

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();

    const pair<int, int> boardXY = setBoardXY();
    WINDOW* boardWin = initNewin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        BOARD_SIZE * BOARD_COLS + 3,
        boardXY.first, boardXY.second);

    const pair<int, int> boatMenuXY = setBoatMenuXY(boats,boardXY);
    WINDOW* boatMenuWin = initNewin(
        BOARD_SIZE * BOARD_ROWS + BOARD_ROWS + 1,
        ((boats.size() + 1) * BOARD_COLS)-1,
        boatMenuXY.first, boatMenuXY.second);

    wrefresh(boardWin);

    drawBoard(boardWin);
    drawBoatMenu(boatMenuWin, boats);

    wrefresh(boardWin);
    wrefresh(boatMenuWin);

    movePlayer(boardWin);

    delwin(boardWin);
    endwin();

    return 0;
}
