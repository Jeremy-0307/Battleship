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

    } while (ch != '\n');

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

void applyOffset(vector<xy>& pts, xy d) {
    for (auto& p : pts) {
        p.x += d.x;
        p.y += d.y;
    }
}

xy pivotOf(const vector<xy>& pts) {
    return pts.front();   // first point as pivot (grid space)
}


vector<xy> rotateRight(const vector<xy>& pts, xy pivot) {     // 90° CW
    vector<xy> out = pts;
    for (auto& p : out) {
        int x = p.x - pivot.x;
        int y = p.y - pivot.y;
        p.x = pivot.x + y;
        p.y = pivot.y - x;
    }
    return out;
}

vector<xy> rotateLeft(const vector<xy>& pts, xy pivot) {      // 90° CCW
    vector<xy> out = pts;
    for (auto& p : out) {
        int x = p.x - pivot.x;
        int y = p.y - pivot.y;
        p.x = pivot.x - y;
        p.y = pivot.y + x;
    }
    return out;
}

void moveBoat(WINDOW* w, vector<xy>& pts, chtype bchar) {
    xy offset{0, 0}, prevOffset{0, 0};
    int ch = 0;
    int limit = BOARD_SIZE - 1;

    do {
        draw(w, bTransform(pts), EMPTY, 1);

        xy nextOffset = offset;
        vector<xy> trial = pts;
        bool rotated = false;

        switch (ch) {
            case KEY_LEFT:  case 'a': case 'A': nextOffset.x--; break;
            case KEY_RIGHT: case 'd': case 'D': nextOffset.x++; break;
            case KEY_UP:    case 'w': case 'W': nextOffset.y--; break;
            case KEY_DOWN:  case 's': case 'S': nextOffset.y++; break;
            case 'e': case 'E':
                trial = rotateRight(pts, pivotOf(pts));
                rotated = true;
                break;

            case 'q': case 'Q':
                trial = rotateLeft(pts, pivotOf(pts));
                rotated = true;
                break;
        }

        nextOffset.x = std::clamp(nextOffset.x, 0, limit);
        nextOffset.y = std::clamp(nextOffset.y, 0, limit);

        if (!rotated) {
            applyOffset(trial, {
                nextOffset.x - prevOffset.x,
                nextOffset.y - prevOffset.y
            });
        }

        if (checkValid(w, trial, limit)) {
            pts = std::move(trial);
            if (!rotated) {
                offset = nextOffset;
                prevOffset = offset;
            }
        }

        draw(w, bTransform(pts), bchar, 2);
        wrefresh(w);

    } while ((ch = wgetch(w)) != '\n');
}
