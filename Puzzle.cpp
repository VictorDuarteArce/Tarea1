#include "Puzzle.h"

using namespace std;
Puzzle::Puzzle() {
    size=0;
    board=nullptr;
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
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] == 0){
                e -> i0 = i;
                e -> j0 = j;
                return e;
            }
        }
    }
    //Calcula la heuristica
    e->calculateValue();
    return e;
}

// Dado el nombre de dominio Puzzle (classe) defino la funcion Puzzle
// utiliza el algoritmo A* para resolver el puzzle
void Puzzle::solve(){
    State *e_init= generate_init(); // genera el estado inicial
    if (e_init == nullptr) {
        cout << "No se pudo generar el estado inicial" << endl;
        return;
    }
    int i = 1;
    open->push(e_init); // agrega en los abierto el tablero inicial
    all->push(e_init->id); // agrega en todos (ex cerrados)el tablero inicial
    while (!open->isEmpty()){ // mientras existan nodos por visitar
        //printf("Open %d\n", i);
        //open->print();
        State* e = open->pop(); // deberia obtener el mejor estado
        //printf("Estado actual: %llu i0: %d j0: %d parent:%p\n", e->id, e->i0, e->j0, e->parent);
        //printf("All %d\n", i);
        //all->print();
        if (e->isSol()){
            printf("Encontramos la solucion\n");
            e->print();
            return;
        }
        //cout << "Expandiendo el estado" << endl;
        // expandir el estado e --> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        State* e_up = e->up();  // si genera estado invalido, genera nullptr
        //printf("Estado actual: %llu i0: %d j0: %d parent:%p\n", e_up->id, e_up->i0, e_up->j0, e_up->parent);
        if (e_up!=nullptr && // si es valido
                !all->find(e_up->id)){ // si no esta en todos //esta busqueda en la tabla hash es de O(1)
            open->push(e_up); // se ingresa al heap ordenado por la heuristica
            all->push(e_up->id); // se ingresa a la tabla hash para un rapido acceso
        }

        State *e_down = e->down();  // si genera estado invalido, genera nullptr
        //if(e_down != nullptr) printf("Estado actual: %llu i0: %d j0: %d parent:%p\n", e_down->id, e_down->i0, e_down->j0, e_down->parent);
        if (e_down!=nullptr &&
                !all->find(e_down->id)) {
            open->push(e_down);
            all->push(e_down->id);
        }

        State *e_left = e->left();  // si genera estado invalido, genera nullptr
        if (e_left!=nullptr &&
                !all->find(e_left->id)){                 
            open->push(e_left);
            all->push(e_left->id);
        }

        State *e_right = e->right();  // si genera estado invalido, genera nullptr
        if (e_right!=nullptr &&
                !all->find(e_right->id)) {
            open->push(e_right);
            all->push(e_right->id);
        }
        i++;
    }
    cout<< "No se encontro solucion" << endl;
}