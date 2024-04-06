#include "Heap.h"

Heap::Heap(int capacity){
    this->capacity = capacity;
    this->size = 0;
    this->arr = new State*[capacity];
}

Heap::~Heap() {
    delete [] arr;
}

// aqui se define si vamos a mantener el heap como min heap o max heap
// en este caso esta realizando un min heap  --> raiz es el menor
void Heap::push(State* val) {
    if (size == capacity) {
        printf("Heap lleno\n");
        State **arr_tmp = new State*[capacity*2];
        for(int i=0; i<capacity; i++) {
            arr_tmp[i] = arr[i];
        }
        delete [] arr;
        arr = arr_tmp;
        capacity *= 2;
    }
    arr[size] = val;
    size++;
    int i = size-1;
    while(i != 0 && arr[i]->value < arr[(i-1)/2]->value) { // min heap
        State* temp = arr[i]; // realizamos el  swap
        arr[i] = arr[(i-1)/2];
        arr[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

State* Heap::pop(){
    if (size == 0) {
        return nullptr;
    }
    State* val = arr[0]; // retornamos la raiz
    arr[0] = arr[size-1]; // ponemos el ultimo elemento en la raiz
    size--; // disminuimos el tamaño
    int i = 0;
    while(2*i+1 < size) {
        int left = 2*i+1;
        int right = 2*i+2;
        int min = left;
        if (right < size && arr[right]->value < arr[left]->value) {
            min = right;
        }
        if (arr[i]->value < arr[min]->value) {
            break; // ya esta ordenado
        }
        State* temp = arr[i]; // si no cuple orden entonces hacemos el swap
        arr[i] = arr[min];
        arr[min] = temp;
        i = min;
    }
    return val;
}
void Heap::print() {
    putchar('{');
    for(int i=0; i<size; i++) {
        printf("%d ", arr[i]->value);
    }
    putchar('}');
    putchar('\n');
}
bool Heap::isEmpty() {
    return size == 0;
}
bool Heap::find(State* val) {
    for(int i=0; i<size; i++) {
        if (arr[i]->equals(val)) {
            return true;
        }
    }
    return false;
}