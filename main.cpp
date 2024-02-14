#include "obj/Obj.hpp"
#include "obj/player/Player.hpp"
#include "obj/boat/Boat.hpp"
#include "window/WinObj.hpp"
//-----------------------------//
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <utility>
#include <vector>
#include <cstring>
#include <iostream>
#include <cwchar> // unicode
#include <locale>

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

int main() {
  std::locale::global(std::locale("en_US.UTF-8"));
  init();

    // wchar_t wideChars = L'🛥';

    // // Create a cchar_t structure wideChar with attributes A_BOLD and color pair 1
    // cchar_t wideChar;
    // attr_t attributes = A_BOLD | COLOR_PAIR(1);
    // setcchar(&wideChar, &wideChars, attributes, 0, NULL);
    // cchar_t bg = wideChar;
  	

  cchar_t p;
  	p.chars[0] = L'[';
  	p.chars[1] = L' ';	
  	p.chars[2] = L' ';
  	p.chars[3] = L']';

  cchar_t bg;
  	bg.chars[0] = L' ';
  	bg.chars[1] = L'🛥';	
  	bg.chars[2] = L' ';
  	bg.chars[3] = L' ';

    init_pair(1, COLOR_RED, COLOR_BLACK); 
    bg.attr = A_BOLD | COLOR_PAIR(1); 


  int maxY = 0, maxX = 0;
  getmaxyx(stdscr, maxY, maxX);
  // 2 extra para los limites
  const int height = 10 + 2;
  const int width = (10 * 4 ) + 2; 
  // poscicionar pantalla
  const int start_y = (maxY - height) / 2;
  const int start_x = (maxX - width) / 2;

  // h&w, x&y
  WinObj comadreja(height, width, start_y, start_x, bg);
  refresh();
  wrefresh(comadreja.w);

  Player jeremy({{0, 0}}, p, &comadreja);
  jeremy.Move(5, 5);


  //Boat bote({{5, 5}}, "[🛥️]", &comadreja);
  
  //bote.Move(0, 0);
  endwin();
};

//📍
//[\u25FC\u25FC]"