#include "Player.hpp"
#include <ncurses.h>
#include <algorithm>
#include <queue>

Player::Player(coordVec coords, const cchar_t &symbol, WinObj *w)
    : Obj(coords, symbol, w) {
  ReadLast();
}

Player::~Player() {}

void Player::Print() {
  for (const auto &coord : coords) {
    int x = 1 + coord.first * w->sizeStr;
    int y = coord.second + 1;

    chtype ch = mvwinch(w->w, y, x);
    int color_pair = PAIR_NUMBER(ch & A_COLOR);
    short fg, bg;
    pair_content(color_pair, &fg, &bg);
    init_pair(3, COLOR_RED, bg);

    wattron(w->w, A_BOLD | COLOR_PAIR(3));
    mvwprintw(w->w, y, x, "%lc", symbol.chars[0]);
    mvwprintw(w->w, y, 3 + x, "%lc", symbol.chars[3]);
    wattroff(w->w, A_BOLD | COLOR_PAIR(3));
  }
  wrefresh(w->w);
  refresh();
}

auto Player::ValidPos(int x, int y) { return Obj::ValidPos(x, y); }

void Player::ReadLast() {
  lastStrs.clear();
  for (const auto &c : coords) {
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
  for (const auto &s : lastStrs) {
    mvwadd_wch(w->w, s.first.second, s.first.first, &s.second);
  }
}

void Player::Move(int axisX, int axisY) {
  bool isValid;
  coordVec newCoords;

  std::tie(isValid, newCoords) = ValidPos(axisX, axisY);

  if (isValid) {
    coords = std::move(newCoords);
    PrintLast();
    ReadLast();
  }
}
