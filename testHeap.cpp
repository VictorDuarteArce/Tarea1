#include "Heap.h"

int main() {
    Heap *h = new Heap(2);
    for(int i=0; i<100; i++) {
        h->push(i);
    }

    for(int i=0; i<100; i++) {
        std::cout << h->pop() << std::endl;
    }
}