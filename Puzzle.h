#include <iostream>
#include "Heap.h"
using namespace std;

class Puzzle {
    public: 
        int **board;  // la matriz que representa el puzzle original
        int size;
        Heap *open; // repositorio de estados por visitar
        Hash *all; // repositorio de de todos los estados que fueron ya generados (esto puede crecer mucho)
        Puzzle();
        Puzzle(char * filename); // cargar desde filename el tablero inicial
        ~Puzzle();
        State * generate_init(); // genera el estado inicial desde board
        void solve(); // opera el algoritmo A*
};