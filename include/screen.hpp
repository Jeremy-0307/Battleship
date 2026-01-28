#pragma once

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BOARD_SIZE 10
#define BOARD_COLS 4
#define HEADER_COLS 3
#define BOARD_ROWS 2
#define EMPTY "."

using std::pair;
using BoatList = std::vector<std::pair<int, std::string>>;

WINDOW* initNewin(int h, int w, int starty, int startx);

pair<int, int> setBoardXY();
pair<int, int> setBoatMenuXY(const BoatList& boats, const pair<int, int>& boardX);

void drawBoard(WINDOW* w);
void drawBoatMenu(WINDOW* w, const BoatList& boats);
void initmenu();
