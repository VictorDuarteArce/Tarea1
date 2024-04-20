#include "State.h"

int main(){
    State *e = new State(5);
    int**board = new int*[*e->size];
    for(int i = 0; i < *e->size; i++){
        board[i] = new int[*e->size];
    }
    int k = 1;
    for(int i = 0; i < *e->size; i++){
        for(int j = 0; j < *e->size; j++){
            board[i][j] = k % (*e->size * *e->size);
            k++;
        }
    }
    e->setId(board);
    *e->depth = 0;
    printf("id: %lu \nid1: %lu\n", *e->id, *e->id1);
    e->print_board();
    int*zero = e->find(0);
    *e->i0 = zero[0];
    *e->j0 = zero[1];
    e->calculateHeuristic();
    printf("heuristic: %f\n", *e->heuristic);
    State *e_up = e->up();
    if(e_up == nullptr){
        printf("No se puede mover\n");
    }else{
        printf("id: %lu \nid1: %lu\n", *e_up->id, *e_up->id1);
        e_up->print_board();
        e_up->calculateHeuristic();
        printf("heuristic: %f\n", *e_up->heuristic);
    }
    return 0;
}