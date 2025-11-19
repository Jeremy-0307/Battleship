// n() {
//     initscr();
//     keypad(stdscr, TRUE);
//     noecho();
//     curs_set(0);

//     WINDOW* boatMenu = nullptr;

//     int user_x = (initX + (SIZEBOARD + 1) /2 * BOARD_COLS) - 1;
//     int user_y =  initY + (SIZEBOARD + 1) /2 * BOARD_ROWS;
//     int key;

//     mvprintw(2, 5, "user_x[%d], user_y[%d]",user_x, user_y);
//     do {
//         refresh();
//         key = getch();
//         #if DEBUG
//             mvprintw(2, 5, "user_x[%d], user_y[%d]",user_x, user_y);
//             //user_x += 1 * BOARD_COLS;
//         #endif
//         mvprintw(user_y, user_x, " . ");
//         move(&user_x, &user_y, &key);
//         mvprintw(user_y, user_x, "[A]");
//     } while (key != 'q');

//     endwin();
//     return 0;
// }
