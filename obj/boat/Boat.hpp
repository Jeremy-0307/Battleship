#ifndef BOAT_HPP
#define BOAT_HPP

#include "../Obj.hpp"

class Boat : public Obj {
 public:
  Boat(coordVec coords, const cchar_t& symbol, WinObj* w);
  ~Boat();

  void ClearPos();
  void Move(int axisX = 0, int axisY = 0);
  void Print();
  auto ValidPos(int x, int y);
  void Move(coordVec coords);
  coordVec Rotate(int side);

};

#endif  // BOAT_HPP
