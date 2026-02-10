#pragma once

#include "../include/screen.hpp"

#include "../include/player.hpp"

enum class Rot : int { R0=0, R90=1, R180=2, R270=3 };


int pickBoat(WINDOW* w, vector<pair<vector<xy>, bool>>& bMenu);

void applyOffset(vector<xy>& pts, xy d);
void moveBoat(WINDOW* w, vector<xy>& pts, chtype bchar);
vector<xy> bTransform(vector<xy> pts);
