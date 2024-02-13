#include "Player.hpp"
#include <ncurses.h>

Player::Player(coordVec coords, const cchar_t& symbol, WinObj* w) : Obj(coords, symbol, w) {
  ReadLast();
}

Player::~Player() {}

void Player::Print() {
  Obj::Print();
}

bool Player::ValidPos(int x, int y) {
   return Obj::ValidPos(x, y);
}

void printcchar(WinObj* w, int x, int y, cchar_t* cchar) {
  mvwin_wch(w->w, 1+y, 1+x*w->sizeStr, cchar); 
}

void Player::ReadLast() {
    lastStrs.clear();
    for (const auto& c : coords) {
        for (int i = 0; i < 4; ++i) {
            cchar_t cchar;
            mvwin_wch(w->w, 1 + c.second, i + 1 + c.first * w->sizeStr, &cchar);
            lastStrs.push_back({{i+c.first, c.second}, cchar});
        }
    }
}

void Player::PrintLast() {
    int contador = 0;
    for (const auto& s : lastStrs) {
      mvwadd_wch(w->w, 1 + s.first.second,  contador+1 + (s.first.first-contador)* w->sizeStr, &s.second);
      contador = (contador==4)?0:contador+1;
    }
}


void Player::Move(int axisX, int axisY) {
  int ch = 0;
  // para imprimir la primera
  while (true) {
    if (axisY || axisX) {
      if (ValidPos(axisX, axisY)){
        PrintLast();
        ReadLast();
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
