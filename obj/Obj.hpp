#ifndef OBJ_HPP
#define OBJ_HPP

#include "../window/WinObj.hpp"
//------------------//
#include <curses.h>
#include <ncurses.h>
#include <utility>
#include <tuple>
#include <vector>

using coord = std::pair<int, int>;
using coordVec = std::vector<coord>;

class Obj {
public:
  coordVec coords;
  cchar_t symbol;
  int limx, limy;
  WinObj *w;

  Obj(coordVec coords, const cchar_t &symbol, WinObj *w);
  ~Obj();

  std::tuple<bool, coordVec> ValidPos(int x, int y);
  void Move();
  void Print();
  void ReadLastPos();
};

#endif // OBJ_HPP
