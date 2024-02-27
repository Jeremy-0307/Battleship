#include "Boat.hpp"

#include <curses.h>



Boat::~Boat() {}

void Boat::Print() {
 // wattron(w->w, A_BOLD | COLOR_PAIR(2));
  for (const auto& coord : coords) {
    int y = coord.second + 1;
    int x = 1 + coord.first * w->sizeStr;
    mvwprintw(w->w, y, x, "%ls", symbol.chars);
  }
  //wattroff(w->w, A_BOLD | COLOR_PAIR(2));
}

Boat::Boat(coordVec coords, const cchar_t& symbol, WinObj* w)
    : Obj(coords, symbol, w) {

  Print();
}