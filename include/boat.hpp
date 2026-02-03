#pragma once

#include "../include/boat.hpp"

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <algorithm>

using std::pair;
using std::vector;
using xy = pair<int, int>;
using boat = pair<vector<xy>, char>;

void boatHighlighter(WINDOW* w, std::pair<int, int> coords, int size, std::pair<int, int> direction);
