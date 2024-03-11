#include <algorithm>
#include <cstdlib> // syscalls
#include <iostream>
#include <queue>
#include <stdio.h> // in/output
#include <string>
#include <tuple>
#include <utility> // std::Pair<,>
#include <vector>

#define cols 10
#define rows 10

//------------------------------------------//
// string lol
typedef std::string string;
// pair<int, int> coordinates
typedef std::pair<int, int> pii;
// vector of coordinates
typedef std::vector<pii> coords;
// vector string
typedef std::vector<std::vector<std::string>> vs;
// vector of boats
struct Boat {
  string symbol;
  coords crds;
};
// vector of Boats
typedef std::vector<Boat> vb;
// player struct
struct Player {
  string symbol;
  string last;
  coords crds;
};
//------------------------------------------//
// metood para hacer busqueda de la posicion de todas las celdas en 'b' que sean
// iguales a 's'
coords bfs(const int x, const int y, const string s, const vs &b) {
  coords newCoords;
  std::queue<pii> q;
  std::vector<pii> visited;

  if (!isdigit(s[5])) {
    return {};
  }

  q.push({x, y});
  visited.push_back({x, y});
  newCoords.push_back({x, y});

  int dx[] = {0, 0, -1, 1};
  int dy[] = {-1, 1, 0, 0};

  while (!q.empty()) {
    pii current = q.front();
    q.pop();

    int cx = current.first;
    int cy = current.second;

    for (int i = 0; i < 4; ++i) {
      int nx = cx + dx[i];
      int ny = cy + dy[i];

      if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
        auto position =
            std::find(visited.begin(), visited.end(), std::make_pair(nx, ny));
        if (position == visited.end() && b[nx][ny] == s) {
          q.push({nx, ny});
          visited.push_back({nx, ny});
          newCoords.push_back({nx, ny});
        }
      }
    }
  }
  return newCoords;
};

// imprime una matrix
void printMatrix(const vs &m) {
  for (auto &row : m) {
    for (auto &cell : row) {
      std::cout << cell << ".";
    }
    std::cout << std::endl;
  }
}

// llena una matrix
void fillMatrix(vs &m) {
  for (size_t i = 0; i < m.size(); ++i) {
    for (size_t j = 0; j < m[i].size(); ++j) {
      m[i][j] = ".";
    }
  }
};

// mueve al jugador en una direccion
void MovePlayer(Player &P, vs &board) {
  for (auto &c : P.crds) {
    P.last = board[c.first][c.second];
    board[c.first][c.second] = P.symbol;
  }
};

// limpia la ultima posicion del jugador para no borrar caracteres
void cleanLast(coords &co, vs &board, string s, bool mb) {
  for (auto &c : co) {
    board[c.first][c.second] = (mb) ? "." : s;
  }
};

// se fija si esta dentro de los limites
inline bool withinBounds(int x, int y) {
  return (x >= 0 && x < cols && y >= 0 && y < rows);
};

// se fija si las nuevas coordenadas estan dentro
coords Valid(int deltaX, int deltaY, const coords &curr, vs &board, bool mb) {
  coords newCoords;
  for (auto &c : curr) {
    int x = c.first + deltaX;
    int y = c.second + deltaY;
    if (!withinBounds(x, y)) {
      return {};
    }
    if (mb) {
      if (board[x][y] != "." && board[x][y] != board[c.first][c.second]) {
        return {};
      }
    }
    newCoords.push_back({x, y});
  }
  return newCoords;
};

// obtiene el index del bote
int getBoatIndex(const vb &LB, string s) {
  for (int i = 0; i < LB.size(); ++i) {
    if (LB[i].symbol == s) {
      return i;
    }
  }
  // claramente retorna -1 si no lo encuentra
  return -1;
};

// mueve el bote, talvez lo pueda borrar con el de moverjugador y llamarle
// MovObj
void moveBoat(coords co, vs &board, string s) {
  for (auto &c : co) {
    board[c.first][c.second] = s;
  }
}

// una vara para debuggear
void debug(Player P) {
  printf("---------\n");
  std::cout << "[" << P.last << "]";
  printf("\n---------\n");
}

// si tuviera que hacer un comentario
// no me gusta como tengo que 10/03/2024
// retorna si se movio deacuerdo a AWSD
std::tuple<int, int> AWSD(int ch) {
  int x = 0, y = 0;
  switch (ch) {
  case 'w':
    x = -1;
    break;
  case 's':
    x = +1;
    break;
  case 'd':
    y = +1;
    break;
  case 'a':
    y = -1;
    break;
  default:
    return {0, 0};
    break;
  }
  return {x, y};
}

// uff no me acuerdo fijjo despue slo necesitoc
void movToPos(vs &v, const coords &co, string s) {
  for (auto c : co) {
    v[c.first][c.second] = s;
  }
}

// metodo para mover los botes o soltar el bote
void selectBoat(vb &LB, Player &P, vs &board, bool &mb) {
  static coords tempC;
  static string tempS;
  static int bID;
  if (mb) {
    LB[bID].crds = P.crds;
    moveBoat(LB[bID].crds, board, LB[bID].symbol);
    P.symbol = tempS;
    P.crds = tempC;
    tempC = P.crds;
    mb = false;
  } else {
    tempC = P.crds;
    P.crds = bfs(P.crds[0].first, P.crds[0].second, P.last, board);
    if (!P.crds.empty()) {
      tempS = P.symbol;
      mb = true;
      bID = getBoatIndex(LB, P.last);
      P.symbol = "\033[31m" + string(1, P.last[5]) + "\033[0m";
    } else {
      P.crds = tempC;
    }
  }
};

// se fija si hay espacio libre en el tablero y coloca el bote ahi una vez lo
// selecciona en el menu
coords searchSpace(const coords &co, const vs &m) {
  int currCount = 0, total = co.size();
  int sizeX = m.size(), sizeY = m[0].size();
  coords space;
  for (int i = 0; i < sizeX; ++i) {
    for (int j = 0; j < sizeY; ++j) {
      for (int k = 1; k < total; ++k) {
        int x = i + co[k].first;
        int y = j + co[k].second;
        if (m[x][y] == " ") {
          currCount += 1;
          space.push_back({x, y});
        } else {
          break;
        }
      }
      if (currCount == total) {
        return space;
      }
      space.clear();
    }
  }
  return {};
};

// metodo principal para setear los botes antes de comenzar el juego
void setBoats(vb &LB, Player &P, vs &board) {
  vs menuBoat(5, std::vector<string>(4));

  int bLeft = LB.size() - 1, total = bLeft + 1;
  int currB = 0;
  int x = 0, y = 0;

  bool onBoat = false, onBoard = false, ready = false, mb = false;
  coords PCrdsBucket;

  while (!ready) {
    int ch = std::cin.get();

    printMatrix(board);
    std::tie(x, y) = AWSD(ch); // llena x,y si se movio con AWSD

    if (!x || !y) { // Si no presiono AWSD
      switch (ch) {
      case 'b':        // en caso de 'b' de BOTE
        if (onBoard) { // si estoy en el tablero
          selectBoat(LB, P, board,
                     mb); // seleccionar si quiere mover bote donde estoy
                          // si no hay un bote donde estoy no hacer nada
                          // o si ya tenia uno seleccionado; lo suelto
        } else {          // en caso de que estuviera en el menu
          // significa que tengo que buscar espacio para colocar el bote
          coords searchSpaceCoords = searchSpace(LB[currB].crds, board);
          // si hay espacio
          if (!searchSpaceCoords.empty()) {
            /** P R O B L E M AS
             * 1. tengo que borrar el bote de la lista para que ya no se pueda
             *imprimir en las opciones de los botes disponibles por poner
             * 2. hacer que P de una sola vez este en movimiento... no dificil?
             * podria utilizar una combinacion de las funcoines que ya tengo
             **/
            // actualizo las coordenadas del bote
            LB[currB].crds = searchSpaceCoords;
            // actualizo las coordenadas del jugador con las del bote en
            // movimiento
            P.crds = searchSpaceCoords;
            // moving boat -> el bote se va estar moviendo
            // y va estar en el tablero
            mb = true, onBoard = true;
            // tambien se decrementa la cantidad de botes restastes por colocar
            bLeft--;
          } else {
            // sino, imprimir que no hay suficiente espacio y mover botes
            // actualmente posicionados
            printf("There's not enough space :( |\nMove your current Boats!");
          }
        }
        break;
      case 'm': // switch entre en menu y el board
        onBoard = !onBoard;
        PCrdsBucket = P.crds;
        cleanLast(PCrdsBucket, board, P.last, onBoat);
        P.crds = {{1, 1}};
        break;
      case 'q':
        ready = true;
        break;
      default:
        break;
      }
    } else if (!onBoat) {
      coords NwCrds = Valid(x, y, P.crds, board, onBoat);
      if (NwCrds.size()) {
        cleanLast(NwCrds, board, P.last, onBoat);
        P.crds = NwCrds;
        MovePlayer(P, board);
      }
    } else {
      currB = (currB + x) % bLeft;
    }
  }
};

int main() {
  int gameOver = false;

  Boat B1;
  B1.crds = {{1, 2}, {3, 1}, {3, 2}, {2, 2}};
  B1.symbol = "\033[32m7\033[0m";
  Boat B2;
  B2.crds = {{2, 2}, {1, 2}};
  B2.symbol = "\033[32m8\033[0m";

  vb LB;
  LB.push_back(B1);
  LB.push_back(B2);

  Player P;
  P.crds = {{1, 1}};
  P.symbol = "\033[31mP\033[0m";
  P.last = ".";

  vs board(4, std::vector<std::string>(4));

  return 0;
};
