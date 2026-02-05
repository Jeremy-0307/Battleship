# Readme

## Por hacer

1. modificar para permitir multiples formas de botes
  - caja de seleccion de bote
  - mover bote

2. highligher functoin



## Logica del juego y estructura de archivos

## main

initncurses(); // para iniciar ncurses
initgame() {
  // crear tableros   
    1. verificar y obtener tamaño de la terminal
    2. iniciar pantallas necesarias para el tablero
      - screenMain
      - screenAttack
      - screenBoats
      - screenScore
  // inicializar botes
    1. Crear botes de un archivo que tome formas y convierta en coordenadas iniciales
}
gamelogic() {
  // colocar botes en la pantalla "while botes in main < than botes in menu" 
  // jugar
  1. escoger donde atacar
  2. atakar
    - negativo: blanco
    - positivo: rojo
      - verificar botes enemigos vivos
    - imprimir log del atacque 
  3. turno del enemigo
  4. repetir mientras botes hundidos del enemigo o mios != enemig.botes();
}

main() {
  initncurses();
  gamelogic();
}
