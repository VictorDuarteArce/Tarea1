#include "State.h"

int main(){
    State *e = new State(4);
    int**board = new int*[e->size];
    for(int i = 0; i < e->size; i++){
        board[i] = new int[e->size];
    }
    int k = 0;
    for(int i = 0; i < e->size; i++){
        for(int j = 0; j < e->size; j++){
            board[i][j] = k % (e->size * e->size);
            k++;
        }
    }
    e->setId(board);
    printf("id: %llu \nid1: %llu\n", e->id, e->id1);
    e->print_board();
    e->i0 = e->find(0)[0];
    e->j0 = e->find(0)[1];
    State *e_copy = e->down();
    printf("id: %llu \nid1: %llu\n", e_copy->id, e_copy->id1);
    e_copy->print_board();
    e->calculateValue();
    printf("isSol: %d\n", e->isSol());
    printf("hits: %d", e->hits);
    return 0;
}