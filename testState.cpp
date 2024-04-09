#include "State.h"

int main(){
    State *e = new State(4);
    int**board = new int*[e->size];
    for(int i = 0; i < e->size; i++){
        board[i] = new int[e->size];
    }
    int k = 1;
    for(int i = 0; i < e->size; i++){
        for(int j = 0; j < e->size; j++){
            board[i][j] = k % (e->size * e->size);
            k++;
        }
    }
    e->setId(board);
    e->print_board();
    e->i0 = e->size - 1;
    e->j0 = e->size - 1;
    State *e_copy = e->left();
    printf("id: %llu\n", e_copy->id);
    e_copy->print_board();
    e->calculateValue();
    printf("isSol: %d\n", e->isSol());
    printf("hits: %d", e->hits);
    return 0;
}