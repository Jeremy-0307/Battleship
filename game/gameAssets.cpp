#include "obj/boat/Boat.hpp"
//-----------------------------//
#include <curses.h>
#include <locale>
#include <ncurses.h>
#include <utility>
#include <vector>

int maxY = 0, maxX = 0;
getmaxyx(stdscr, maxY, maxX);

const int height = 10 + 2;
const int width = (10 * 4) + 2;
const int start_y = (maxY - height) / 2;
const int start_x = (maxX - width) / 2;
//extern
WinObj mainScreen(height, width, start_y, start_x, bg);

// extern
std::vector<Boat> LBoats(5);
    
	cchar_t strB;
		init_pair(2, COLOR_BLACK, COLOR_GREEN);
		strB.attr = A_BLINK | COLOR_PAIR(2);
		strB.chars[0] = L'[';
		strB.chars[2] = L' ';
		strB.chars[3] = L']';

	strB.chars[1] = L'🛥';
	LBoats[0] = Boat({{1, 2}, {2, 2}, {3, 2}, {3, 1}}, strB, &w);

	strB.chars[1] = L'⛵';
	LBoats[1] = Boat({{1, 3}}, strB, &w);

	strB.chars[1] = L'🛳';
	LBoats[2] = Boat({{1, 3}}, strB, &w);

	strB.chars[1] = L'𓊝';
	LBoats[3] = Boat({{1, 3}}, strB, &w);

	strB.chars[1] = L'⛴';
	LBoats[4] = Boat({{1, 3}}, strB, &w);



cchar_t p;
  init_pair(1, COLOR_RED, COLOR_BLACK);
  p.attr = COLOR_PAIR(1);
  // setcchar(&p, &wideChars, A_BLINK | COLOR_PAIR(1), 0, NULL);
  p.chars[0] = L'[';
  p.chars[1] = L' ';
  p.chars[2] = L' ';
  p.chars[3] = L']';
// extern
Player P({{0, 0}}, p, &mainScreen);


