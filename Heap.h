#include <iostream>
#include "Hash.h"

class Heap {
public:
    State **arr; // Arreglo de estados
    int capacity;
    int size; // indice del ultimo no ocupado o cantidad de elementos
    Heap(int capacity);
    ~Heap();
    void push(State* val);
    State* pop();
    void print();
    bool isEmpty();
    bool find(State* val);
};