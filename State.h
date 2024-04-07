#include <iostream>
class State {
    public:
        int id; // identificador del estado
        int **board; // tablero size x size
        int size;
        // al cargar el archivo busco donde esta el 0
        int i0; //fila del cero
        int j0; // columna del cero
        State *parent;
        int value; // valor de la heuristica
        State();
        State(int size);
        State(int size, State *parent);
        State(int size, State *parent, int **board);
        bool isSol(); // verifica si es solucion
        ~State();
        void print(); // print recursively
        void print_board();
        State *up();
        State *down();
        State *left();
        State *right();
        State *copy();
        bool equals(State *s); // compara dos estados
        //bool equals(State *s); // compara dos estados
        void calculateValue(); // calcula el valor de la heuristica
};