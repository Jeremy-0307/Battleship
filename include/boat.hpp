#pragma once

// inline vs constexpr
// inline    = una sola definicion a pesar de multiples llamados del header
// constexpr = pista a compilador que se puede definidir en compilacion

#include <utility>
#include <vector>
#include <ncurses.h>
#include <algorithm>
#include <ranges>

constexpr const char* BCH = "o";

using std::pair;
using std::vector;
struct xy {
    int x = 0;
    int y = 0;
};
using boat = pair<vector<xy>, const char*>;

// Empiezan de 0,0
// ----------------------------------
// 0    0    0
// 0    0   000
// 0    0  0   0
// 0  000  0   0
inline vector<boat> boats = {
    { {{0,2},{0,1},{0,0},{0,3},{0,4}}, BCH },
    { {{2,2},{2,1},{2,0},{2,3},{1,3},{0,3}}, BCH },
    { {{2,1},{2,0},{1,1},{3,1},{0,2},{4,2},{0,3},{4,3}}, BCH }
};

inline const int bQuant = static_cast<int>(boats.size());
inline int totalBoatWidth() {
    int width = 0;
    for (const auto& b : boats) {
        auto [minIt, maxIt] = std::minmax_element(
            b.first.begin(),
            b.first.end(),
            [](const xy& a, const xy& b) {
                return a.x < b.x;
            }
        );
        width += maxIt->x - minIt->x + 1;
    }
    return width;
}
const int bWidth = totalBoatWidth();
