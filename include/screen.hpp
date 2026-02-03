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

// Boat Menu Screen
#define MAX_WITDH 20

using std::vector;
using std::pair;

WINDOW* initNewin(int h, int w, int starty, int startx);

pair<int, int> setBoardXY();
pair<int, int> setBoatMenuXY(const int bWidth, const int quantBoats, const pair<int, int>& boardXY);
void drawBoard(WINDOW* w);
void drawBoatMenu(WINDOW* w, const vector<boat>& boats);
void initmenu();
