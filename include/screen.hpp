#pragma once

#include "boat.hpp"

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

// Main Screen
#define BOARD_SIZE 10
#define BOARD_COLS 4
#define HEADER_COLS 3
#define BOARD_ROWS 2
#define EMPTY "."

WINDOW* initWin(int h, int w, int x, int y);
WINDOW* initBoard(const xy& origin);
WINDOW* initMenu(const xy& boardOrigin);

xy getBoardOrigin();
xy getMenuOrigin(const xy& boardOrigin);

void highligher(WINDOW* w, char c, vector<xy> Coords, short color);
void drawBoard(WINDOW* w);
void drawMenu(WINDOW* w);
void initmenu();
