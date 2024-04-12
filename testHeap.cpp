#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    for(int i=0; i<128; i++){
        State *s = new State();
        s->heuristic = i;
        h->push(s);
    }

    for(int i=0; i<128; i++){
        State *s = h->pop();
        printf("%d\n", s->heuristic);
    }
}