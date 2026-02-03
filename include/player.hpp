#pragma once

#include "../include/screen.hpp"

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <algorithm>

#define EMPTY "."

void movePlayer(WINDOW* w);

void pickBoat(WINDOW* w, std::vector<std::pair<int,std::string>> boats);
void moveBoat(WINDOW* w);
