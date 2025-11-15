    #include <string>
    #include <ncurses.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <thread>   // For std::this_thread::sleep_for
    #include <chrono>   // For std::chrono::milliseconds

    #define DEBUG 1
    #define SIZEBOARD 10
    #define SPACE_COLS 3
    #define SPACE_ROWS 2
    #define EMPTY "."

    static std::string boat_board[SIZEBOARD][SIZEBOARD];
    static std::string attack_board[SIZEBOARD][SIZEBOARD];

    void setscreen(int* initX, int* initY);
    void initboard();

    void sleep_ms(int mls) {
        std::this_thread::sleep_for(std::chrono::milliseconds(mls));
    }

    void initboard(int* initX, int* initY) {
        setscreen(initX, initY);

        for (int column = 0; column <= SIZEBOARD; ++column) {
            for (int row = 0; row <= SIZEBOARD; ++row) {
                int screenCOL = *initX + (column * SPACE_COLS);
                int screenROW = *initY + (row * SPACE_ROWS);

                if (row == 0 && column == 0) {
                    continue;
                }
                else if (column == 0) {
                    mvprintw(screenROW, screenCOL, "%d", row - 1);
                }
                else if (row == 0) {
                    mvprintw(screenROW, screenCOL, "%c", 'A' + (column - 1));
                }
                else {
                    mvprintw(screenROW, screenCOL, "%s", EMPTY);
                }
            }
            printw("\n");
        }
        refresh();
    }

    void setscreen(int* initX, int* initY) {
        int max_x, max_y;
        getmaxyx(stdscr, max_y, max_x);

        int total_cols = (SIZEBOARD + 1) * SPACE_COLS;
        int total_rows = (SIZEBOARD + 1) * SPACE_ROWS;

        *initX = (max_x - total_cols) / 2;
        *initY = (max_y - total_rows) / 2;
        #if DEBUG
            mvprintw(5, 5, "max_x[%d]   -   max_y[%d]", max_x, max_y);
            mvprintw(6, 5, "total_rows[%d]   -   total_cols[%d]", total_rows, total_cols);
            mvprintw(7, 5, "initX[%d]   -   initY[%d]", *initX, *initY);
        #endif
    }

    void printuser(int* user_x, int* user_y){
        mvprintw(*user_y, *user_x, "[ . ]");
    }

    void move(int* user_x, int* user_y, int* key) {
        switch (*key) {
            case KEY_LEFT:
                (*user_x) -= SPACE_COLS;
                break;
            case KEY_RIGHT:
                (*user_x) += SPACE_COLS;
                break;
            case KEY_DOWN:
                (*user_y) += SPACE_ROWS;
                break;
            case KEY_UP:
                (*user_y) -= SPACE_ROWS;
                break;
        }
        if (*user_x <= 1){
            (*user_x) = 2;
        }
        else if (*user_y  <= 1) {
            (*user_y) = 2;
        }
        else if (*user_x >= SIZEBOARD*SPACE_COLS) {
            (*user_x) = SIZEBOARD*(SPACE_COLS-1);
        }
        else if (*user_y  >= SIZEBOARD*SPACE_ROWS) {
            (*user_y) = SIZEBOARD*(SPACE_ROWS-1);
        }
    }

    int main() {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        int initX, initY;
        initboard(&initX, &initY);
        int user_x = (initX+SIZEBOARD*SPACE_COLS)/2, user_y = (initY+SIZEBOARD*SPACE_ROWS)/2, prev_x = 0, prev_y = 0;
        int key;
        do {
            key = getch();

            prev_x = user_x, prev_y = user_y;
            #if DEBUG
                mvprintw(2, 2, "user_x[%d], user_y[%d]",user_x, user_y);
            #endif
            move(&user_x, &user_y, &key);
            mvprintw(user_y, user_x, "[.]");
            refresh();
        } while (key != 'q');

        endwin();
        return 0;
    }
