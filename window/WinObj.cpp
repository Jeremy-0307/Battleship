#include "WinObj.hpp"

#include <cstdlib>
#include <cstring>
#include <cwchar>

WinObj::WinObj(int height, int width, int x, int y, const cchar_t& s)
    : height(height), width(width) {
  w = newwin(height, width, x, y);
  refresh();
  sizeStr = wcslen(s.chars);

  box(w, 0, 0);
  int num_horizontal_marks = width / 4;
  for (int y_coord = 1; y_coord < height - 1; y_coord++) {
    mvwprintw(w, y_coord, 0, "%d", y_coord - 1);
    for (int x_coord = 0; x_coord < num_horizontal_marks; ++x_coord) {
      int x_offset = x_coord * sizeStr;
      mvwprintw(w, y_coord, 1 + x_offset, "%ls", s.chars);
      mvwprintw(w, 0, 3 + x_offset, "%d", x_coord);
    }
  }
}

WinObj::~WinObj() {}

void WinObj::CheckSize(/*int x, int y*/) {}
