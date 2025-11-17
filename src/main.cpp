    #include <string>
    #include <ncurses.h>
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <thread>   // For std::this_thread::sleep_for
    #include <chrono>   // For std::chrono::milliseconds

    #define DEBUG 1
    #define SIZEBOARD 10
    #define SPACE_COLS 4
    #define SPACE_ROWS 2
    #define EMPTY "."

    static std::string boat_board[SIZEBOARD][SIZEBOARD];
    static std::string attack_board[SIZEBOARD][SIZEBOARD];

    int initX, initY;

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
        if (*user_x <= initX){
            (*user_x) = (initX + SPACE_COLS) - 1;
        }
        else if (*user_y  <= initY) {
            (*user_y) = initY + SPACE_ROWS;
        }
        else if (*user_x >= initX + SIZEBOARD * SPACE_COLS) {
            (*user_x) = (initX + SIZEBOARD * SPACE_COLS) - 1;
        }
        else if (*user_y  >= initY + SIZEBOARD * SPACE_ROWS) {
            (*user_y) = initY + SIZEBOARD * SPACE_ROWS;
        }
    }

    int main() {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        initboard(&initX, &initY);
        int user_x = (initX + (SIZEBOARD+1)/2 * SPACE_COLS) - 1;
        int user_y =  initY + (SIZEBOARD+1)/2 * SPACE_ROWS;
        int prev_x = 0, prev_y = 0, key;

        mvprintw(2, 5, "user_x[%d], user_y[%d]",user_x, user_y);
        do {
            refresh();
            key = getch();
            prev_x = user_x, prev_y = user_y;
            #if DEBUG
                mvprintw(2, 5, "user_x[%d], user_y[%d]",user_x, user_y);
                //user_x += 1 * SPACE_COLS;
            #endif
            mvprintw(user_y, user_x, " . ");
            move(&user_x, &user_y, &key);
            mvprintw(user_y, user_x, "[A]");
        } while (key != 'q');

        endwin();
        return 0;
    }
