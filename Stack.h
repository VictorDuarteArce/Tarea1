#include <iostream>
#include "State.h"

using namespace std;

class Stack {
public:
    State **data; // diseño: se va disponer de un arreglo de punteros a estados
    int size; // este es el tamaño del arreglo
    int top; // el elemento de arriba del stack, -1 significa que esta vacio

    Stack(int n);
    Stack(); /// Default constructor
    ~Stack();
    bool isEmpty();
    void push(State *s); // s deberia tener su memoria propia 
    State * pop();
    bool find(State *e); // dice si e estab dentro del stack
};