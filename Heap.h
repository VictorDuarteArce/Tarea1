#include <iostream>

class Heap {
public:
    int *arr;
    int capacity;
    int size; // indice del ultimo no ocupado o cantidad de elementos
    Heap(int capacity);
    ~Heap();
    void push(int val);
    int pop();
};