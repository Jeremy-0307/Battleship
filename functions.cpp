#include "window/WinObj.hpp"
/******************/
#include <algorithm>
#include <queue>
#include <vector>

std::vector<std::pair<int, int>> bfs(const WinObj *window, int targetValue,
                                     int startX, int startY) noexcept {
  //                                        abaj      arrib   izq,     der
  const std::pair<int, int> Directions[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
  std::queue<std::pair<int, int>> Queue;
  std::vector<std::pair<int, int>> Visited;

  cchar_t first;
  mvwin_wch(window->w, 1 + startY, 2 + startX * window->sizeStr, &first);
  mvprintw(12, 1, "[%lc] .vs [%lc]", first.chars[0], targetValue);

  if (first.chars[0] == targetValue) {
    Queue.push({startX, startY});
    Visited.push_back({startX, startY});
  } else {
    return {};
  }

  while (!Queue.empty()) {
    int currentX = 2 + Queue.front().first * window->sizeStr,
        trueX = Queue.front().first;
    int currentY = 1 + Queue.front().second, trueY = Queue.front().second;
    Queue.pop();

    for (const auto &direction : Directions) {
      int nextX = currentX + direction.first * 4;
      int nextY = currentY + direction.second;

      if (nextX >= 0 && nextX < window->width && nextY >= 0 &&
          nextY < window->height) {
        cchar_t character;
        mvwin_wch(window->w, nextY, nextX, &character);
        if (character.chars[0] == targetValue) {
          int rawX = trueX + direction.first, rawY = trueY + direction.second;
          auto position = std::find(Visited.begin(), Visited.end(),
                                    std::make_pair(rawX, rawY));
          if (position == Visited.end()) {
            Visited.push_back({rawX, rawY});
            Queue.push({rawX, rawY});
          }
        }
      }
    }
  }
  return Visited;
}

void printPos(std::vector<std::pair<int, int>> &pos) {
  int cont = 0;
  for (const auto &p : pos) {
    // mvprintw(12, 1 + cont * 5, "[%d,%d]", p.first, p.second);
    cont++;
  }
}
