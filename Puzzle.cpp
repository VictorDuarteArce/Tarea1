#include "Puzzle.h"

using namespace std;

Puzzle::Puzzle() {
    size = 0;
    board = nullptr;
    open = new Heap(100);
    all = new Hash();
}

State * Puzzle::generate_init(){
    // asumiendo que board ya esta cargado
    State *e = new State(size, nullptr, board);
    e->id = 0;
    e->parent=nullptr;
    e->i0=-1; // caso de no encontrar el cero
    e->j0=-1;
    e->value = 0;
    e->level = 0;
    if (board==nullptr) {
        cout << "No se ha cargado el tablero" << endl;
        return nullptr;
    }
    //generar id
    e->setId(board);
    // buscar el cero
    int* zero = e->find(0);
    if (zero == nullptr) {
        cout << "No se encontro el cero" << endl;
        return nullptr;
    }
    e->i0 = zero[0];
    e->j0 = zero[1];
    //Calcula la heuristica
    e->calculateValue();
    return e;
}

// Dado el nombre de dominio Puzzle (classe) defino la funcion Puzzle
// utiliza el algoritmo A* para resolver el puzzle
void Puzzle::solve(){
    State* e_init= generate_init(); // genera el estado inicial
    if (e_init == nullptr) {
        printf("No se pudo generar el estado inicial\n");
        return;
    }
    int i = 1;
    open->push(e_init); // agrega en los abierto el tablero inicial
    all->push(e_init->id, e_init->id1); // agrega en todos (ex cerrados)el tablero inicial
    while (!open->isEmpty()){ // mientras existan nodos por visitar
        //printf("Open %d\n", i);
        //open->print();
        State* e = open->pop(); // deberia obtener el mejor estado
        //printf("Estado actual: %llu %llu i0: %d j0: %d parent:%p\n", e->id, e->id1, e->i0, e->j0, e->parent);
        //printf("All %d\n", i);
        //all->print();
        if (e->isSol()){
            printf("Encontramos la solucion\n");
            e->print();
            return;
        }
        //cout << "Expandiendo el estado" << endl;
        // expandir el estado e --> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        State* e_up = e->up();
        //printf("Estado actual: %llu %llu i0: %d j0: %d parent:%p\n", e_up->id, e_up->id1, e_up->i0, e_up->j0, e_up->parent);
        //printf("up\n");
        //e_up->print_board();
        if (e_up != nullptr && // si es valido
                !all->find(e_up->id, e_up->id1)){ // si no esta en todos //esta busqueda en la tabla hash es de O(1)
            open->push(e_up); // se ingresa al heap ordenado por la heuristica
            all->push(e_up->id, e_up->id1); // se ingresa a la tabla hash para un rapido acceso
        }

        State *e_down = e->down();
        //if(e_down != nullptr) printf("Estado actual: %llu i0: %d j0: %d parent:%p\n", e_down->id, e_down->i0, e_down->j0, e_down->parent);
        //printf("down\n");
        //e_down->print_board();
        if (e_down!=nullptr &&
                !all->find(e_down->id, e_down->id1)){
            open->push(e_down);
            all->push(e_down->id, e_down->id1);
        }

        State *e_left = e->left();
        //printf("left\n");
        //e_left->print_board();
        if (e_left!=nullptr &&
                !all->find(e_left->id, e_left->id1)){
            open->push(e_left);
            all->push(e_left->id, e_left->id1);
        }

        State *e_right = e->right();
        //printf("right\n");
        //e_right->print_board();
        if (e_right!=nullptr &&
                !all->find(e_right->id, e_right->id1)) {
            open->push(e_right);
            all->push(e_right->id, e_right->id1);
        }
        i++;
    }
    cout<< "No se encontro solucion" << endl;
}