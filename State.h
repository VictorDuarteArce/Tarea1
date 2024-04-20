#include <iostream>
class State {
    public:
        long unsigned int *id; // identificador del estado
        long unsigned int *id1;
        int *size;
        // al cargar el archivo busco donde esta el 0
        int *i0; //fila del cero
        int *j0; // columna del cero
        State *parent;
        float *heuristic; // valor de la heuristica
        int *distance; // distancia de manhattan
        int *misses; // aciertos
        int *depth; // nivel del arbol
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
        void calculateHeuristic(); // calcula el valor de la heuristica
        void calculateMisses(); // calcula los aciertos
        void calculateDistance(); // calcula la distancia
        int* find(int value); // busca la posicion de un valor
        void setId(int** board); // genera el id a partir del tablero
        int** getBoard(); //genera el tablero a partir de una id
};