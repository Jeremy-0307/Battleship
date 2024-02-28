  #ifndef PLAYER_HPP
  #define PLAYER_HPP

  #include "../Obj.hpp"

  class Player : public Obj {
  public:
    std::vector<std::pair<coord, cchar_t>> lastStrs;

    Player(coordVec coords, const cchar_t &symbol, WinObj *w);
    ~Player();
    void Move(int axisX = 0, int axisY = 0);
    void Print();
    void ReadLast();
    auto ValidPos(int x, int y);
    void PrintLast();
  };

  #endif // PLAYER_HPP
