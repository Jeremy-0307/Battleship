#ifndef OBJ_HPP
#define OBJ_HPP

#include "../window/WinObj.hpp"
//------------------//
#include <utility>
#include <ncurses.h>
#include <vector>
#include <curses.h>
#include <string>
#include <cwchar>
#include <locale>

using coord = std::pair<int, int>;
using coordVec = std::vector<coord>;

class Obj { 
public:
    coordVec coords;  
    cchar_t symbol;
    int limx, limy; 
    WinObj* w;

    Obj(coordVec coords, const cchar_t& symbol, WinObj* w);
    ~Obj();

    bool ValidPos(int x, int y);
    void Move();
    void Print();
    void ReadLastPos();

};

#endif // OBJ_HPP

