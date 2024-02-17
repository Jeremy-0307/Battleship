#include "Boat.hpp"

#include <curses.h>

Boat::Boat(coordVec coords, const cchar_t& symbol, WinObj* w)
    : Obj(coords, symbol, w) {

  //Print();
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

bool Boat::ValidPos(int x, int y) { return Obj::ValidPos(x, y); }

void Boat::Move(coordVec coords) {
  int axisY = 0, axisX = 0;
  int ch = 0;
  coords = coords;
  while (true) {
    if (axisY || axisX) {
      if (ValidPos(axisX, axisY)) {
        //PrintLast(axisX, axisY);
        //ReadLast();
        Print();
        wrefresh(w->w);
        refresh();
      }
    }

    axisY = 0, axisX = 0;
    ch = getch();

    switch (ch) {
      case KEY_UP:
        axisY = -1;
        break;
      case KEY_DOWN:
        axisY = 1;
        break;
      case KEY_LEFT:
        axisX = -1;
        break;
      case KEY_RIGHT:
        axisX = 1;
        break;
      case 'q':
        endwin();
        return;
    }
  }
}
