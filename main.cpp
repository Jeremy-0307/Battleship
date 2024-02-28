#include "obj/Obj.hpp"
#include "obj/boat/Boat.hpp"
#include "obj/player/Player.hpp"
#include "window/WinObj.hpp"
//-----------------------------//
#include <curses.h>
#include <locale>
#include <ncurses.h>
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

using coord = std::pair<int, int>;
using coordVec = std::vector<coord>;


extern coordVec bfs(const WinObj *window, int targetValue, int startX, int startY) noexcept;

int main() {
  int adios = 10;
  std::locale::global(std::locale("en_US.UTF-8"));
  init();

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
  boat.chars[0] = L'[';
  boat.chars[1] = L'🛥';
  boat.chars[2] = L' ';
  boat.chars[3] = L']';

  int maxY = 0, maxX = 0;
  getmaxyx(stdscr, maxY, maxX);

  const int height = 10 + 2;
  const int width = (10 * 4) + 2;
  const int start_y = (maxY - height) / 2;
  const int start_x = (maxX - width) / 2;

  WinObj main(height, width, start_y, start_x, bg);

  Player P({{0, 0}}, p, &main);
  Boat B({{1, 2}, {2, 2}, {3, 2}, {3, 1}}, boat, &main);

  bool cicle = true, MovingBoat = false;
  coordVec temp, rotation;
  while (cicle) {
    int axisX = 0, axisY = 0;
    int c = getch();
    switch (c) {
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
    case 'a':
      if (MovingBoat) {
        rotation = B.Rotate();
        P.coords = rotation;
        B.coords = rotation;
      }
      break;
    case 'b':
      temp = P.coords;
      P.coords = std::move(bfs(&main, L'🛥', P.coords[0].first, P.coords[0].second));
      MovingBoat = true;
      break;
    case 'q':
      endwin();
      cicle = false;
      break;
    default:
      break;
    }
    if (c != 'q') {
      P.Move(axisX, axisY);
      if (MovingBoat) {
        B.Move(axisX, axisY);
      }
    }
  }
  refresh();
  wrefresh(main.w);
  endwin();
};
// 📍
