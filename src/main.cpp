#include <string>
#include <utility>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

#include "../include/screen.hpp"
#include "../include/player.hpp"
#include "../include/boat.hpp"

void initncurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();
    curs_set(0);
    refresh();
}

int main() {
    initncurses();

    const xy boardOrigin = getBoardOrigin();
    WINDOW* boardScreen = initBoard(boardOrigin);
    drawBoard(boardScreen);
    wrefresh(boardScreen);

    const xy menuOrigin = getMenuOrigin(boardOrigin);
    WINDOW* menuScreen = initMenu(menuOrigin);
    drawMenu(menuScreen);
    wrefresh(menuScreen);

    while(wgetch(menuScreen) != 'q');

    delwin(boardScreen);
    delwin(menuScreen);
    endwin();

    return 0;
}
