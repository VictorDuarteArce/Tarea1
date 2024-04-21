#include "Hash.h"
#include <random>
#define LENGTH 1000 //raíz de la cantidad de elementos a insertar
//se insertarán LENGTH^2 elementos en la tabla hash

int main(){ //El objetivo de este test es probar la estructura AVL
    Hash* hash = new Hash();
    for(int i = 0; i < LENGTH; i++){ 
        for(int j = 0; j < LENGTH; j++){
            State* state = new State(3);
            *state->id = i;
            *state->id1 = j;
            printf("%llu %llu\n", *state->id, *state->id1);
            hash->push(*state->id, *state->id1); //Debería insertar todos los elementos en un O(log(n)/1000) promedio
        }
    }
    hash->print();
    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < LENGTH; j++){
            State* state = new State();
            *state->id = i;
            *state->id1 = j;
            printf("%d", hash->find(*state->id, *state->id1));
            delete state;
        }
    }
    return 0;
}