#include "Obj.hpp"

Obj::Obj(coordVec coords, const cchar_t& symbol, WinObj* w)
    : coords(coords), symbol(symbol), w(w) {
  getmaxyx(w->w, limy, limx);

  limy -= 3;
  limx = (limx - w->sizeStr) / w->sizeStr;
}

Obj::~Obj() {}

void Obj::Print() {
  // wattron(w->w, A_BOLD | COLOR_PAIR(2));
  // for (const auto& coord : coords) {
  //   int y = coord.second + 1;
  //   int x = 1 + coord.first * w->sizeStr;
  //   mvwprintw(w->w, y, x, "%lc", symbol.chars[0]);
  // }
  // wattroff(w->w, A_BOLD | COLOR_PAIR(2));
}

std::tuple<bool, coordVec> Obj::ValidPos(int x, int y) {
  std::vector<std::pair<int, int>> newCoords;

  for (const auto& c : coords) {
    int tempx = c.first + x;
    int tempy = c.second + y;
    if (tempx < 0 || tempx > limx || tempy < 0 || tempy > limy) {
      return {false, {}};
    }
    newCoords.emplace_back(tempx, tempy);
  }
  return {true, newCoords};
}
