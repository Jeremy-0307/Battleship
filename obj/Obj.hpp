#ifndef OBJ_HPP
#define OBJ_HPP

#include "../window/WinObj.hpp"
//------------------//
#include <curses.h>
#include <ncurses.h>

#include <cwchar>
#include <locale>
#include <string>
#include <utility>
#include <vector>

using coord = std::pair<int, int>;
using coordVec = std::vector<coord>;

class Obj {
 public:
  coordVec coords;
  cchar_t symbol;
  int limx, limy;
  WinObj* w;

  Obj(coordVec coords, const cchar_t& symbol, WinObj* w);
  ~Obj();

  bool ValidPos(int x, int y);
  void Move();
  void Print();
  void ReadLastPos();
};

#endif  // OBJ_HPP
