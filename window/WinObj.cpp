#include "WinObj.hpp"
#include <cstring>
#include <cwchar>
#include <cstdlib>


void Printcchar(WINDOW* w, int x, int y, cchar_t* wideChar, int n) {
    for (int i = 0; i < n; ++i) {
        mvwadd_wch(w, y, x + i, wideChar);
    }
}

WinObj::WinObj(int height, int width, int x, int y, const cchar_t& s) : height(height), width(width) {
    w = newwin(height, width, x, y);
    refresh();
    sizeStr = wcslen(s.chars);
    for (int x = 1; x < height-1; x++) {
        for (int y = 1; y < width-1; y += sizeStr) {
            mvwprintw(this->w, x, y, "%ls", s.chars); 
        }
    }
    box(w, 0, 0);
}

WinObj::~WinObj() {}

void WinObj::CheckSize(/*int x, int y*/) {}
