#ifndef BOAT_HPP
#define BOAT_HPP

#include "../Obj.hpp"

class Boat : public Obj {
 public:
  Boat(coordVec coords, const cchar_t& symbol, WinObj* w);
  ~Boat();

  void Move(int axisX = 0, int axisY = 0);
  void Print();
  bool ValidPos(int x, int y);
  void Move(coordVec coords);
};

#endif  // BOAT_HPP
