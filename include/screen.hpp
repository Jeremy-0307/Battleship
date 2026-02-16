#pragma once

#include "boat.hpp"

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BOARD_SIZE 10
#define BOARD_COLS 4
#define BOARD_ROWS 2
#define HEADER_COLS 3
#define EMPTY_1 " "
#define EMPTY_2 "."

WINDOW* initBoard(const xy& origin);
WINDOW* initMenu(const xy& boardOrigin);

xy getBoardOrigin();
xy getMenuOrigin(const xy& boardOrigin);

void initmenu();
void drawBoard(WINDOW* w);
void draw(WINDOW* w, const vector<xy>& pts, const char* ch, const int colorID = 1);

vector<pair<vector<xy>,bool>> drawMenu(WINDOW* w);

bool checkValid(WINDOW* w, const vector<xy>& pts, int limit);

int boatCoords(WINDOW* w, const xy& c);
