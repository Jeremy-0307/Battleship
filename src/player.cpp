#include "../include/player.hpp"

int pickBoat(WINDOW* w, vector<pair<vector<xy>, bool>>& bMenu) {
    int curr = 0, prev = 0, ch = 0;
    while (!bMenu[curr].second)
        curr = (curr + 1) % bQuant;

    do {
        prev = curr;
        switch (ch) {
            case KEY_LEFT: case 'a': case 'A':
                do {
                    curr = (curr - 1 + bQuant) % bQuant;
                } while (!bMenu[curr].second);
                break;
            case KEY_RIGHT: case 'd': case 'D':
                do {
                    curr = (curr + 1) % bQuant;
                } while (!bMenu[curr].second);
                break;
        }

        draw(w, bMenu[prev].first, BCH, 1);
        draw(w, bMenu[curr].first, BCH, 2);
        wrefresh(w);

        ch = wgetch(w);

    } while (ch != '\n' && ch != 27);
    if(ch == 27) return 27;

    bMenu[curr].second = false;
    return curr;
}

vector<xy> bTransform(vector<xy> pts) {
    for (auto& p : pts) {
        p.x = p.x * BOARD_COLS + HEADER_COLS;
        p.y = p.y * BOARD_ROWS + BOARD_ROWS;
    }
    return pts;
}

void applyOffset(vector<xy>& pts, const xy& d) {
    for (auto& p : pts) {
        p.x += d.x;
        p.y += d.y;
    }
}

static inline xy deltaFromKey(int ch) {
    switch (ch) {
        case KEY_LEFT:  case 'a': case 'A': return {-1,  0};
        case KEY_RIGHT: case 'd': case 'D': return { 1,  0};
        case KEY_UP:    case 'w': case 'W': return { 0, -1};
        case KEY_DOWN:  case 's': case 'S': return { 0,  1};
        default: return {0, 0};
    }
}

static inline int rotateFromKey(int ch) {
    switch (ch) {
        case 'e': case 'E': return  1;
        case 'q': case 'Q': return -1;
        default: return 0;
    }
}

void rotate(bool clockwise, vector<xy>& point) {
    const xy pivot = point[0];
    for (auto& p : point) {
        xy out{0,0};
        int x = p.x - pivot.x;
        int y = p.y - pivot.y;

        if (clockwise) {
            out.x = pivot.x + y;
            out.y = pivot.y - x;
        } else {
            out.x = pivot.x - y;
            out.y = pivot.y + x;
        }

        p = out;
    }
}

void movePlayer(WINDOW* w, const vector<pair<vector<xy>, bool>>& bMenu) {
    keypad(w, TRUE);

    vector<xy> pos = { {0, 0} }, tmp, screen = bTransform(pos);
    xy move{0, 0};

    const int limit = BOARD_SIZE - 1;
    bool onBoat = false;

    draw(w, { { screen[0].x - 1, screen[0].y } }, "[.]", 2);
    wrefresh(w);

    int ch;
    while ((ch = wgetch(w)) != 27) {
        if (ch == '\n' && onBoat) break;

        move = deltaFromKey(ch);
        if (move.x == 0 && move.y == 0) continue;

        tmp = pos;
        applyOffset(tmp, move);
        if (!checkValid(w, tmp, limit)) continue;

        if (onBoat) {
            draw(w, screen, " o ", 1);
            onBoat = false;
        } else{
            draw(w, { { screen[0].x - 1, screen[0].y } }, " . ", 1);
        }

        auto g = bTransform(tmp);
        chtype cell = mvwinch(w, g[0].y, g[0].x);
        size_t i = 0;

        if ((cell & A_CHARTEXT) == BCH[0]) {
            tmp = boats[boatCoords(w, tmp[0])].first;
            onBoat = true;
            if (ch == 27) { // ENTER
                //for (const auto& p : pos) --p.x;
                moveBoat(w, tmp);

            } else { // JUST PASSING TRU

                pos = std::move(tmp);
                screen = bTransform(pos);
                for (auto& p : screen) --p.x;
                draw(w, screen, "[o]", 2);
            }
        } else {
            pos = std::move(tmp);
            screen = bTransform(pos);
            draw(w, { { screen[0].x - 1, screen[0].y } }, "[.]", 2);
        }

        wrefresh(w);
    }
}

void moveBoat(WINDOW* w, vector<xy>& pos) {
    keypad(w, TRUE);
    const int limit = BOARD_SIZE - 1;

    draw(w, bTransform(pos), BCH, 2);
    wrefresh(w);

    int ch = 0;
    while ((ch = wgetch(w)) != '\n') {
        const xy move = deltaFromKey(ch);
        const int rot = rotateFromKey(ch);

        if (rot == 0 && move.x == 0 && move.y == 0) continue;

        draw(w, bTransform(pos), ".", 1);

        auto tmp = pos;

        if (rot != 0) {
            const bool clockwise = (rot == -1);
            rotate(clockwise, tmp);
        } else {
            applyOffset(tmp, move);
        }

        if (checkValid(w, tmp, limit)) {

            pos = std::move(tmp);
        }
        draw(w, bTransform(pos), BCH, 2);
        wrefresh(w);
    }
}
