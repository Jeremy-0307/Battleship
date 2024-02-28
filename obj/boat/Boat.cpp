#include "Boat.hpp"

#include <curses.h>

Boat::~Boat() {}

void Boat::Print() {
  for (const auto &c : coords) {
    int y = c.second + 1;
    int x = 1 + c.first * w->sizeStr;
    mvwprintw(w->w, y, x, "%ls", symbol.chars);
  }
}

Boat::Boat(coordVec coords, const cchar_t& symbol, WinObj* w)
    : Obj(coords, symbol, w) {
  Print();
}

void Boat::ClearPos() {
  for (const auto &c : coords) {
    int y = c.second + 1;
    int x = 1 + c.first * w->sizeStr;
    mvwprintw( w->w, y, x, "....");
  }
}

auto Boat::ValidPos(int x, int y) {
  return Obj::ValidPos(x, y);
}

void Boat::Move(int axisX, int axisY){
  bool isValid;
  coordVec newCoords;

  std::tie(isValid, newCoords) = ValidPos(axisX, axisY);

  if (isValid) {
    ClearPos();
    coords = std::move(newCoords);
    wattron(w->w, A_BOLD | COLOR_PAIR(3));
    Print();
    wattroff(w->w, A_BOLD | COLOR_PAIR(3));
    wrefresh(w->w);
    refresh();
  }
}

coordVec Boat::Rotate() {
    coordVec newCoords;
    int anclaX = coords[0].first; 
    int anclaY = coords[0].second; 

    for (const auto &c : coords) {
      int newX = anclaX - (c.second - anclaY);
      int newY = anclaY + (c.first - anclaX);

      newCoords.push_back({newX, newY});
    }
  return newCoords;
}

