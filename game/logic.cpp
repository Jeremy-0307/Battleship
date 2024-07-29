// extern std::vector<Boat> LBoats(5); // lista de botes
// extern Player P();

// void prepareAssets() {
//   // inicializa todo y trae todo lo que se ocupe
// }

// // escoger las posiciones de la lista de botes
// void setBoats(std::vector<Boat> LB, winObj MENU, winObj MAIN) {
//   // asumiendo que ya todo esta inicializado
//   // P comienza en W[lista de botes];
//   int boatsLeft = LB.size();
//   int c = 0, axisY;
//   while (boatsLeft) {
//     B *currentBoat = nullptr;
//     while (!currentBoat) {
//       switch (c) {
//       case KEY_UP:
//         axisY = (axisY + 1 > P.w->height) ? axisY : axisY + 1;
//         break;
//       case KEY_DOWN:
//         axisY = (axisY - 1 < 1) ? axisY : axisY - 1;
//         break;
//       case 'b':
//         currentBoat = &LB[axisY];
//         break;
//       default:
//         break;
//       }
//       currentBoat = nullptr;
//       moveBoat(currentBoat);

//       // iterar por los botes;
//       // puedo tener solo los emojis por el momento
//       /**
//        * toda la logia para moverse por el tablero; puedo hacer esta funcion en
//        *functions.cpp o en WinObj
//        **/
//       // if c = B
//       // currentBoat = bote sobre esta el P ; si es que hay un boet
//     }
//     // cambia la W del bote de menu -> board
//     // se posiciona sobre el board
//     // moveBoat(currentBoat)
//   }
// }

// void moveBoat(Bote &B) {
//   // algun algoritmo para encontrar donde hay espacio en el tablero para color
//   // por primera
//   //  vez el bote
//   bool movingBoat = true;
//   B->w = board;
//   int c = getch();
//   int axisY = 0, axisX = 0;
//   6 switch (c) {
//   case KEY_UP:
//     axisY = -1;
//     break;
//   case KEY_DOWN:
//     axisY = 1;
//     break;
//   case KEY_LEFT:
//     axisX = -1;
//     break;
//   case KEY_RIGHT:
//     axisX = 1;
//     break;
//   case 'a':
//     if (MovingBoat) {
//       rotation = B.Rotate(1);
//       if (!rotation.empty()) {
//         P.coords = rotation;
//         B.coords = rotation;
//       }
//     }
//     break;
//   case 'd':
//     if (MovingBoat) {
//       rotation = B.Rotate(-1);
//       if (!rotation.empty()) {
//         P.coords = rotation;
//         B.coords = rotation;
//       }
//     }
//     break;
//   case 'b':
//     if (MovingBoat) {
//       P.coords = temp;
//       MovingBoat = false;
//       B.Print();
//     } else {
//       temp = P.coords;
//       P.coords = bfs(&mainScreen, L'🛥', P.coords[0].first, P.coords[0].second);
//       mvprintw(9, 1, "Size: [%d]", P.coords.size());
//       if (!P.coords.empty()) {
//         MovingBoat = true;
//       } else {
//         P.coords = temp;
//       }
//     }
//     break;
//   }
//   // movimiento normal
//   // si c = esc -> con bote: devolver bote; sin bote: volver a menu
//   // de aqui; que retorne un -1 si lo coloco y un 0 si no lo coloco |||||
//   // si c = b colocar / escoger bote
// }

// // cuando set boats acabe
// void start() {
//   // si ya todos los jugadores tienen sus botes listos
//   // else{
//   // no se... algo deberia de pasar aqui lol
//   // while (gameOver) //
//   // moverse normal
//   // si es turno; verificar con un booleano/int
//   // si c = A y XY != [X]
//   // attack() if 1 -> verde [X] else rojo [X]
//   // verificar victoria
//   // turno de AI ..
// }

// void attack() {
//   //
// }
