#include "Player.hpp"

#include <ncurses.h>

#include <algorithm>
#include <queue>

auto bfs(const WinObj* window, int targetValue, int startX, int startY) noexcept {
//                                           abajo ,  arriba, izq,     der   
  const std::pair<int, int> Directions[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
  std::queue<std::pair<int, int>> Queue;
  std::vector<std::pair<int, int>> Visited;

  Queue.push({startX, startY});
  Visited.push_back({startX, startY});

  while (!Queue.empty()) {
    int currentX = 2 + Queue.front().first * window->sizeStr,
        trueX = Queue.front().first;
    int currentY = 1 + Queue.front().second,
        trueY = Queue.front().second;
    Queue.pop();

    for (const auto& direction : Directions) {
      int nextX = currentX + direction.first * 4;
      int nextY = currentY + direction.second;

      if (nextX >= 0 && nextX < window->width && nextY >= 0 &&
          nextY < window->height) {
        cchar_t character;
        mvwin_wch(window->w, nextY, nextX, &character);
        if (character.chars[0] == targetValue) {
          int rawX = trueX + direction.first, rawY = trueY + direction.second;
          auto position = std::find(Visited.begin(), Visited.end(), std::make_pair(rawX, rawY));
          if (position == Visited.end()) {
            Visited.push_back(
                {rawX, rawY});
            Queue.push({rawX, rawY});
          }
        }
      }
    }
  }
  return Visited;
}

Player::Player(coordVec coords, const cchar_t& symbol, WinObj* w)
    : Obj(coords, symbol, w) {
  ReadLast();
}

Player::~Player() {}

void Player::Print() {
  for (const auto& coord : coords) {
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
}

bool Player::ValidPos(int x, int y) { return Obj::ValidPos(x, y); }

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
  //this->coords = bfs(w, L'2', 1, 2);
  //axisY = 1;
  while (true) {
    if (axisY || axisX) {
      if (ValidPos(axisX, axisY)) {
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
