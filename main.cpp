#include "obj/Obj.hpp"
#include "obj/boat/Boat.hpp"
#include "obj/player/Player.hpp"
#include "window/WinObj.hpp"
//-----------------------------//
#include <curses.h>
#include <ncurses.h>

#include <algorithm>  // for std::find
#include <cstring>
#include <cwchar>  // unicode
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <vector>

void init() {
  initscr();
  noecho();
  curs_set(0);
  start_color();
  use_default_colors();
  cbreak();
  keypad(stdscr, TRUE);
}

extern auto bfs(WinObj* w, int value, int startX, int startY) noexcept;

using coord = std::pair<int, int>;
using coordVec = std::vector<coord>;

int main() {
  std::locale::global(std::locale("en_US.UTF-8"));
  init();

  int hola = 0;

  cchar_t p;
  init_pair(1, COLOR_RED, COLOR_BLACK);
  p.attr = A_BLINK | COLOR_PAIR(1);
  // setcchar(&p, &wideChars, A_BLINK | COLOR_PAIR(1), 0, NULL);
  p.chars[0] = L'[';
  p.chars[1] = L' ';
  p.chars[2] = L' ';
  p.chars[3] = L']';

  cchar_t bg;
  bg.chars[0] = L'.';
  bg.chars[1] = L'.';
  bg.chars[2] = L'.';
  bg.chars[3] = L'.';

  cchar_t boat;
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  boat.attr = A_BLINK | COLOR_PAIR(2);
  boat.chars[0] = L'1';
  boat.chars[1] = L'2';
  boat.chars[2] = L'3';
  boat.chars[3] = L'4';

  //int prueba = boat.chars[1];
  int maxY = 0, maxX = 0;
  getmaxyx(stdscr, maxY, maxX);

  const int height = 10 + 2;
  const int width = (10 * 4) + 2;
  const int start_y = (maxY - height) / 2;
  const int start_x = (maxX - width) / 2;

  WinObj main(height, width, start_y, start_x, bg);

  Player jeremy({{0, 0}}, p, &main);
  Boat b({{1, 2}, {2, 2}, {3, 2}, {3, 1}}, boat, &main);
  jeremy.Move(0, 0);
  b.Move(jeremy.coords);
  // b.Move(5, 5);

  refresh();
  wrefresh(main.w);

  endwin();
};
// 📍