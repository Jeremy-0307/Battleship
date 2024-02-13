// #include "Boat.hpp"
// #include <curses.h>

// Boat::Boat(coordVec coords, const std::wstring& symbol, WinObj* w) : Obj(coords, symbol, w) {
//   //ReadLast();
//   if (ValidPos(0, 0))
//   {
//     Print();
//   }
// }

// Boat::~Boat() {}

// void Boat::Print() {
//   Obj::Print();
// }

// bool Boat::ValidPos(int x, int y) {
//     std::vector<std::pair<int, int>> newCoords;
//     std::vector<chtype> str(w->sizeStr); // Ensure the vector has the correct size
//     for (const auto& c : coords) {
//         int tempx = c.first + x;
//         int tempy = c.second + y;

//         if (tempx < 0 || tempx > limx || tempy < 0 || tempy > limy) {
//             mvwinchnstr(w->w, 1 + c.second, 1 + c.first * w->sizeStr, str.data(), w->sizeStr);
//             const std::wstring strW(str.begin(), str.end()); // Convert chtype vector to wstring
//             if (strW != *w->s) { // Dereference the pointer to compare wstrings
//                 mvprintw(12, 1, "tempx[%d] limx[%d] && tempy[%d] limy[%d]", tempx, limx, tempy, limy);
//                 return false;
//             }
//         }
//         newCoords.emplace_back(tempx, tempy);
//     }
//     coords = std::move(newCoords);
//     return true;
// }





// void Boat::Move(int axisX, int axisY) { }