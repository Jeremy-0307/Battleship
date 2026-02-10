#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

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

    init_pair(1, COLOR_WHITE, -1);
    init_pair(2, COLOR_RED,   -1);
}

int main() {
    initncurses();

    //************** Board **************
        const xy boardOrigin = getBoardOrigin();
        WINDOW* boardScreen = initBoard(boardOrigin);
        wattron(boardScreen, COLOR_PAIR(1));
        drawBoard(boardScreen);
        wattroff(boardScreen, COLOR_PAIR(1));
        wrefresh(boardScreen);

    //************** Menu **************
        const xy menuOrigin = getMenuOrigin(boardOrigin);
        WINDOW* menuScreen = initMenu(menuOrigin);
        wattron(menuScreen, COLOR_PAIR(1));
        auto bMenu = drawMenu(menuScreen);
        wattroff(menuScreen, COLOR_PAIR(1));
        wrefresh(menuScreen);

    //************** Game Logic **************
    // set all boats on screen
    // 1. Pick boat from Menu
    // 2. Put bot on Board
    //  2.1     Make sure to put the boat on screen if possible (find first white space)
    //
    int curr = 0;
    do {
        curr = pickBoat(menuScreen, bMenu);
        std::size_t curr_t = static_cast<std::size_t>(curr);
        if (curr == 27) {
            // move player across the board 'till
            // 1. he returns to Menu
            // 2. picks a boat
        } else {
            draw(menuScreen, bMenu[curr_t].first, ' ');
            moveBoat(boardScreen, boats[curr_t].first, BCH);
        }

    } while (true);
    pickBoat(menuScreen, bMenu);

    delwin(boardScreen);
    delwin(menuScreen);
    endwin();

    return 0;
}
