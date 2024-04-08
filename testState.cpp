#include "State.h"

int main() {
    State *e = new State(3);
    int k = 1;
    for(int i = 0; i < e->size; i++){
        for(int j = 0; j < e->size; j++){
            e->board[i][j] = k%(e->size*e->size);
            k++;
        }
    }
    e->generateId();
    e->i0 = 2;
    e->j0 = 2;
    State *e_up = e->up();
    e_up->generateId();
    State *e_down = e_up->down();
    e_down->generateId();
    State *e_left = e_down->left();
    e_left->generateId();
    State *e_right = e_left->right();
    e_right->generateId();
    e->print_board();
    e_up->print_board();
    e_down->print_board();
    e_left->print_board();
    e_right->print_board();
    printf("e == e_up: %d\n", e->equals(e_up));
    printf("e: %ld\n", e->id);
    printf("e_up: %ld\n", e_up->id);
    return 0;
}