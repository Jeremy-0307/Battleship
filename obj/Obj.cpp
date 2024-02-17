#include "Obj.hpp"

Obj::Obj(coordVec coords, const cchar_t& symbol, WinObj* w)
    : coords(coords), symbol(symbol), w(w) {
  getmaxyx(w->w, limy, limx);

  limy -= 3;
  limx = (limx - w->sizeStr) / w->sizeStr;
};

Obj::~Obj() {}

void Obj::Print() {
  for (const auto& coord : coords) {
    int y = coord.second + 1;
    int x = 1 + coord.first * w->sizeStr;
    mvwprintw(w->w, y, x, "%ls", symbol.chars);
  }
}

bool Obj::ValidPos(int x, int y) {
  std::vector<std::pair<int, int>> newCoords;

  for (const auto& c : coords) {
    int tempx = c.first + x;
    int tempy = c.second + y;

    if (tempx < 0 || tempx > limx || tempy < 0 || tempy > limy) {
      mvprintw(12, 1,
               "Invalid position: tempx[%d] limx[%d] && tempy[%d] limy[%d]",
               tempx, limx, tempy, limy);
      return false;
    }

    newCoords.emplace_back(tempx, tempy);
  }

  coords = std::move(newCoords);
  return true;
}
