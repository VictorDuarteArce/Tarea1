#include "Puzzle.h"

int main() {
    Puzzle *p = new Puzzle();
    p->board = new int*[2];
    p->size = 2;

    for(int i = 0; i < 2; i++) {
        p->board[i] = new int[2];
    }
    p->board[0][0] = 1;
    p->board[0][1] = 0;
    p->board[1][0] = 3;
    p->board[1][1] = 2;

    p->solve();
    
    return 0;
}