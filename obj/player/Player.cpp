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

// void Player::ReadLast() {
//   lastStrs.clear();
//   for (const auto& c : coords) {
//       mvwin_wch(w->w, y,   x, &cchar[0]);
//       lastStrs.push_back({{x, y}, cchar[0]});
//       mvwin_wch(w->w, y, 1+x, &cchar[1]);
//       lastStrs.push_back({{1+x, y}, cchar[1]});
//       mvwin_wch(w->w, y, 2+x,& cchar[2]);
//       lastStrs.push_back({{2+x, y}, cchar[2]});
//       mvwin_wch(w->w, y, 3+x, &cchar[3]);
//       lastStrs.push_back({{3+x, y}, cchar[3]});
//       //mvwin_wch(w->w, y, x, &cchar);
//   }
// }

// void Player::ReadLast() {
//   lastStrs.clear();
//   for (const auto& c : coords) {
//       cchar_t cchar[4];
//       int y = 1 + c.second;
//       int x = 1 + c.first * w->sizeStr;

//       // mvwin_wch(w->w, y, x, &cchar[0]);
//       // lastStrs.push_back({{x, y}, cchar[0]});

//       mvwin_wch(w->w, y, 1+x, &cchar[1]);
//       lastStrs.push_back({{1+x, y}, cchar[1]});

//       mvwin_wch(w->w, y, 2+x, &cchar[2]);
//       lastStrs.push_back({{2+x, y}, cchar[2]});

//       // mvwin_wch(w->w, y, 3+x, &cchar[3]);
//       // lastStrs.push_back({{3+x, y}, cchar[3]});
//   }
// }

void Player::ReadLast() {
  lastStrs.clear();
  for (const auto& c : coords) {
    for (int i = 0; i < 4; ++i) {
      cchar_t cchar;
      int y = 1 + c.second;
      int x = i + 1 + c.first * w->sizeStr;
      mvwin_wch(w->w, y, x, &cchar);
      lastStrs.push_back({{x, y}, cchar});
    }
  }
}

void Player::PrintLast() {
    for (const auto& s : lastStrs) {
      mvwadd_wch(w->w, s.first.second, s.first.first, &s.second);
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
