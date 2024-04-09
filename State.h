#include <iostream>
class State {
    public:
        long long unsigned int id; // identificador del estado
        int size;
        // al cargar el archivo busco donde esta el 0
        int i0; //fila del cero
        int j0; // columna del cero
        State *parent;
        int value; // valor de la heuristica
        int distance; // distancia de manhattan
        int hits; // aciertos
        int level; // nivel del arbol
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
        void calculateHits(); // calcula los aciertos
        void calculateDistance(); // calcula la distancia
        int* find(int value); // busca la posicion de un valor
        void setId(int** board); // genera el id
        void deleteBoard(); // borra el tablero
        int** getBoard(); //genera el tablero a partir de una id
};