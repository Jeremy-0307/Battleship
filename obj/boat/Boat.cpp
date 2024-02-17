#include "Boat.hpp"

#include <curses.h>

Boat::Boat(coordVec coords, const cchar_t& symbol, WinObj* w)
    : Obj(coords, symbol, w) {
  // ReadLast();
  Print();
}

Boat::~Boat() {}

void Boat::Print() {
  wattron(w->w, A_BOLD | COLOR_PAIR(2));
  for (const auto& coord : coords) {
    int y = coord.second + 1;
    int x = 1 + coord.first * w->sizeStr;
    mvwprintw(w->w, y, x, "%ls", symbol.chars);
  }
  wattroff(w->w, A_BOLD | COLOR_PAIR(2));
}

bool Boat::ValidPos(int x, int y) {
  // Assuming you want to check if the position (x, y) is within the window
  // boundaries You may need to implement your own validation logic here
  return Obj::ValidPos(
      x, y);  // Returning the result of the parent class validation function
}

void Boat::Move(int axisX, int axisY) {
  // Obj::Print();
  // Implement the logic to move the boat here
  // You may need to update the boat's coordinates and then call the Print
  // function to redraw it Example: UpdateCoords(axisX, axisY); Print();
}
