#include <string>
#include <utility>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/screen.hpp"

using std::pair;
using BoatList = std::vector<std::pair<int, std::string>>;
BoatList boats = {
    {5, "5"},
    {4, "4"},
    {3, "3"},
    {3, "3"},
    {2, "2"}
};

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();

    const pair<int, int> boardCoords = setBoardXY();
    WINDOW* boardWin = initNewin(
        BOARD_SIZE * BOARD_ROWS,
        BOARD_SIZE * BOARD_COLS,
        boardCoords.first, boardCoords.second);
    box(boardWin, 0, 0);
    wrefresh(boardWin);
    drawBoard(boardCoords.first, boardCoords.second);

    int key = getch();

    delwin(boardWin);
    endwin();

    return 0;
}
