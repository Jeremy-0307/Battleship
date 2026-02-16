#pragma once

#include "../include/screen.hpp"

#include "../include/player.hpp"

int pickBoat(WINDOW* w, vector<pair<vector<xy>, bool>>& bMenu);

void moveBoat(WINDOW* w, vector<xy>& pts);
void movePlayer(WINDOW* w, const vector<pair<vector<xy>, bool>>& bMenu);
vector<xy> bTransform(vector<xy> pts);
