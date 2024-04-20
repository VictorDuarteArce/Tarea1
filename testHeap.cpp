#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    for(int i=0; i<128; i++){
        State *s = new State(5);
        int** board = new int*[*s->size];
        for(int j = 0; j < *s->size; j++){
            board[j] = new int[*s->size];
        }
        for(int j = 0; j < *s->size; j++){
            for(int k = 0; k < *s->size; k++){
                board[j][k] = rand() % (*s->size * *s->size);
            }
        }
        s->depth = new int(i);
        s->setId(board);
        *s->heuristic = rand() % 1000;
        h->push(s);
    }

    for(int i=0; i < 128; i++){
        State *s = h->pop();
        printf("%.1f ", *s->heuristic);
    }
}