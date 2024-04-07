#include "Stack.h"
Stack::Stack(){ // por defecto construye stack de tamaño 100
    size=100;
    data = new State*[size];

}
Stack::Stack(int n) { // construye stack de tamaño n
    data = new State*[n]; // crea memoria para objeto int en arreglo de tamaño n
    size=n;
    top=-1;
}
Stack::~Stack() { // el destructor que libera memoria del sistema
    delete[] data; // esto realiza un free y ademas en modo arreglo
}

bool Stack::isEmpty() {
    return (top==-1); // es nuestra convencion para ver si esta vacio
}

void Stack::push(State* s) {
    if(top==size-1){
        State **data_tmp = new State*[size*2]; // crea un nuevo arreglo de tamaño doble
        for (int i = 0; i < size; i++){
            data_tmp[i] = data[i]; // ######copia los datos del arreglo original al nuevo
        }
        delete[] data; // libera la memoria del arreglo original
        data=data_tmp; // asigna el nuevo puntero a data
        size *=2; // actualiza el tamaño (size = size*2)
    }
    ++top;
    data[top]=s; // ### incrementa top y luego asigna s
} 
State * Stack::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow" << endl;
        return nullptr; // si no puede retorna nulo
    }
    return (data[top--]); // devuelve el puntero y decrementa top
}


bool Stack::find(State * e) {
    for (int i=0; i<=top; i++) {
        if (data[i]->equals(e)) {
            return true;
        }
    }
    return false;
}