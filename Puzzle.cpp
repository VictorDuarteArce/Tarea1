#include "Puzzle.h"

/// Aqui se implementan los cuerpo de las funciones


Puzzle::Puzzle() {
    size=0;
    board=nullptr;
    open = new Stack(100);
    all = new Stack(100);
}

State * Puzzle::generate_init() {
    // asumiendo que board ya esta cargado
    State *e = new State(size, nullptr, board);
    e->parent=nullptr;
    e->i0=-1; // caso de no encontrar el cero
    e->j0=-1;
    if (board==nullptr) {
        cout << "No se ha cargado el tablero" << endl;
        return nullptr;
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

    return e;
}

// Dado el nombre de dominio Puzzle (classe) defino la funcion Puzzle
// utiliza el algoritmo A* para resolver el puzzle
void Puzzle::solve() {
    State *e_init= generate_init(); // genera el estado inicial
    if (e_init==nullptr) {
        cout << "No se pudo generar el estado inicial" << endl;
        return;
    }
    open->push(e_init); // agrega en los abierto el tablero inicial
    all->push(e_init); // agrega en todos (ex cerrados)el tablero inicial
    while (!open->isEmpty()) { // mientras existan nodos por visitar
        State* e = open->pop(); // deberia obtener el mejor estado
        printf("Estado actual: %p i0: %d j0: %d parent:%p\n", e, e->i0, e->j0, e->parent);
        if (e->isSol()) {
            printf("Encontramos la solucion\n");
            e->print();
            return;
        }
        //cout << "Expandiendo el estado" << endl;
        // expandir el estado e --> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        State* e_up = e->up();  // si genera estado invalido, genera nullptr
        if (e_up!=nullptr && // si es valido
                !all->find(e_up)) { // si no esta en todos
            open->push(e_up);
            all->push(e_up);
        }

        State *e_down = e->down();  // si genera estado invalido, genera nullptr
        if (e_down!=nullptr &&
                !all->find(e_down)) {
            open->push(e_down);
            all->push(e_down);
        }

        State *e_left = e->left();  // si genera estado invalido, genera nullptr
        if (e_left!=nullptr &&
                !all->find(e_left)) {
            open->push(e_left);
            all->push(e_left);
        }

        State *e_right = e->right();  // si genera estado invalido, genera nullptr
        if (e_right!=nullptr &&
                !all->find(e_right)) {
            open->push(e_right);
            all->push(e_right);
        }
    }
    cout<< "No se encontro solucion" << endl;


}