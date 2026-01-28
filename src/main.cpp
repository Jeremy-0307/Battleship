#include <string>
#include <utility>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/screen.hpp"
#include "../include/player.hpp"


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
        BOARD_SIZE * (BOARD_ROWS)+BOARD_ROWS+1,
        BOARD_SIZE * (BOARD_COLS)+BOARD_COLS,
        boardCoords.first, boardCoords.second);
    wrefresh(boardWin);
    drawBoard(boardWin, boardCoords.first, boardCoords.second);
    wrefresh(boardWin);


    movePlayer(boardWin);

    delwin(boardWin);
    endwin();

    return 0;
}
