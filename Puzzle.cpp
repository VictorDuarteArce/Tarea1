#include "Puzzle.h"

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
    for(int i = 0; i < e->size; i++){
        for(int j = 0; j < e->size; j++){
            e->id = e->id * e->size * e->size + e->board[i][j];
        }
    }
    // buscar el cero
    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            if(board[i][j] == 0){
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
        if(e_up != nullptr){
            e_up->level = i;
            e_up->parent = e;
            e_up->calculateValue();
            //calcula el id
            for(int i = 0; i < e_up->size; i++){
                for(int j = 0; j < e_up->size; j++){
                    e_up->id = e_up->id * e_up->id * e_up->id + e_up->board[i][j];
                }
            }
            int** aux;
            aux = e_up->board;
            for(int i = 0; i < e_up->size; i++){
                delete [] aux[i];
            }
            delete [] aux;
            e_up->board = nullptr; // borramos la matriz porque ya la tenemos en el id
        }
        if (e_up!=nullptr && // si es valido
                !all->find(e_up->id)) { // si no esta en todos
            open->push(e_up);
            all->push(e_up->id);
        }

        State *e_down = e->down();  // si genera estado invalido, genera nullptr
        if(e_down != nullptr){
            e_down->level = i;
            e_down->parent = e;
            e_down->i0 = e->i0+1;
            e_down->j0 = e->j0;
            e_down->calculateValue();
            //calcula el id
            for(int i = 0; i < e_down->size; i++){
                for(int j = 0; j < e_down->size; j++){
                    e_down->id = e_down->id * e_down->size * e_down->size + e_down->board[i][j];
                }
            }
            int** aux;
            aux = e_down->board;
            for(int i = 0; i < e_down->size; i++){
                delete [] aux[i];
            }
            delete [] aux;
            e_down->board = nullptr;
        }
        if (e_down!=nullptr &&
                !all->find(e_down->id)) {
            open->push(e_down);
            all->push(e_down->id);
        }

        State *e_left = e->left();  // si genera estado invalido, genera nullptr
        if(e_left != nullptr){
            e_left->level = i;
            e_left->parent = e;
            e_left->i0 = e->i0;
            e_left->j0 = e->j0-1;
            e_left->calculateValue();
            //calcula el id
            for(int i = 0; i < e_left->size; i++){
                for(int j = 0; j < e_left->size; j++){
                    e_left->id = e_left->id * e_left->size * e_left->size + e_left->board[i][j];
                }
            }
            int** aux;
            aux = e_left->board;
            for(int i = 0; i < e_left->size; i++){
                delete [] aux[i];
            }
            delete [] aux;
            e_left->board = nullptr;
        }
        if (e_left!=nullptr &&
                !all->find(e_left->id)){
            open->push(e_left);
            all->push(e_left->id);
        }

        State *e_right = e->right();  // si genera estado invalido, genera nullptr
        if(e_right != nullptr){
            e_right->level = i;
            e_right->parent = e;
            e_right->calculateValue();
            //calcula el id
            for(int i = 0; i < e_right->size; i++){
                for(int j = 0; j < e_right->size; j++){
                    e_right->id = e_right->id * e_right->size * e_right->size + e_right->board[i][j];
                }
            }
            int** aux;
            aux = e_right->board;
            for(int i = 0; i < e_right->size; i++){
                delete [] aux[i];
            }
            delete [] aux;
            e_right->board = nullptr;
        }
        if (e_right!=nullptr &&
                !all->find(e_right->id)) {
            open->push(e_right);
            all->push(e_right->id);
        }
        i++;
    }
    cout<< "No se encontro solucion" << endl;
}