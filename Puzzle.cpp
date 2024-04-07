#include "Puzzle.h"

Puzzle::Puzzle() {
    size=0;
    board=nullptr;
    open = new Stack(100);
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
    if (board==nullptr) {
        cout << "No se ha cargado el tablero" << endl;
        return nullptr;
    }
    //generar id
    for(int i = 0; i < e->size; i++){
        for(int j = 0; j < e->size; j++){
            e->id = e->id * 10 + e->board[i][j];
        }
    }
    // buscar el cero
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (board[i][j]==0) {
                e->i0=i;
                e->j0=j;
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
    open->push(e_init); // agrega en los abierto el tablero inicial
    all->push(e_init); // agrega en todos (ex cerrados)el tablero inicial
    while (!open->isEmpty()) { // mientras existan nodos por visitar
        State* e = open->pop(); // deberia obtener el mejor estado
        //printf("Estado actual: %d i0: %d j0: %d parent:%p\n", e->id, e->i0, e->j0, e->parent);
        if (e->isSol()) {
            printf("Encontramos la solucion\n");
            e->print();
            return;
        }
        //cout << "Expandiendo el estado" << endl;
        // expandir el estado e --> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        State* e_up = e->up();  // si genera estado invalido, genera nullptr
        if(e_up != nullptr){
            e_up->parent = e;
            e_up->calculateValue();
            //calcula el id
            for(int i = 0; i < e_up->size; i++){
                for(int j = 0; j < e_up->size; j++){
                    e_up->id = e_up->id * 10 + e_up->board[i][j];
                }
            }
        }
        if (e_up!=nullptr && // si es valido
                !all->find(e_up)) { // si no esta en todos
            open->push(e_up);
            all->push(e_up);
        }

        State *e_down = e->down();  // si genera estado invalido, genera nullptr
        if(e_down != nullptr){
            e_down->parent = e;
            e_down->i0 = e->i0+1;
            e_down->j0 = e->j0;
            e_down->calculateValue();
            //calcula el id
            for(int i = 0; i < e_down->size; i++){
                for(int j = 0; j < e_down->size; j++){
                    e_down->id = e_down->id * 10 + e_down->board[i][j];
                }
            }
        }
        if (e_down!=nullptr &&
                !all->find(e_down)) {
            open->push(e_down);
            all->push(e_down);
        }

        State *e_left = e->left();  // si genera estado invalido, genera nullptr
        if(e_left != nullptr){
            e_left->parent = e;
            e_left->i0 = e->i0;
            e_left->j0 = e->j0-1;
            e_left->calculateValue();
            //calcula el id
            for(int i = 0; i < e_left->size; i++){
                for(int j = 0; j < e_left->size; j++){
                    e_left->id = e_left->id * 10 + e_left->board[i][j];
                }
            }
        }
        if (e_left!=nullptr &&
                !all->find(e_left)){
            open->push(e_left);
            all->push(e_left);
        }

        State *e_right = e->right();  // si genera estado invalido, genera nullptr
        if(e_right != nullptr){
            e_right->parent = e;
            e_right->calculateValue();
            //calcula el id
            for(int i = 0; i < e_right->size; i++){
                for(int j = 0; j < e_right->size; j++){
                    e_right->id = e_right->id * 10 + e_right->board[i][j];
                }
            }
        }
        if (e_right!=nullptr &&
                !all->find(e_right)) {
            open->push(e_right);
            all->push(e_right);
        }
    }
    cout<< "No se encontro solucion" << endl;
}