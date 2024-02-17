#ifndef WINOBJ_HPP
#define WINOBJ_HPP

#include <curses.h>
#include <ncurses.h>

#include <cwchar>  // unicode
#include <locale>
#include <string>

class WinObj {
 public:
  int height, width;
  int limx, limy;
  int sizeStr;
  cchar_t* s;
  WINDOW* w;

  WinObj(int height, int width, int x, int y, const cchar_t& s);

  ~WinObj();

  void CheckSize(/*int x, int y*/);
};

#endif  // WINOBJ_HPP
