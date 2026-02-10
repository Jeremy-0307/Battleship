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
#define EMPTY '.'

WINDOW* initWin(int h, int w, int x, int y);
WINDOW* initBoard(const xy& origin);
WINDOW* initMenu(const xy& boardOrigin);

xy getBoardOrigin();
xy getMenuOrigin(const xy& boardOrigin);

void draw(WINDOW* w, const vector<xy>& pts, char ch = EMPTY, int colorID = 1);
void drawBoard(WINDOW* w);
void initmenu();

vector<pair<vector<xy>,bool>> drawMenu(WINDOW* w);

bool checkValid(WINDOW* w, const vector<xy>& pts, int limit);
