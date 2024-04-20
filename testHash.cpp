#include "Hash.h"
#include <random>
#define LENGTH 1000

int main(){ //El objetivo de este test es probar la estructura AVL
    Hash* hash = new Hash();
    for(int i = 0; i < LENGTH; i++){ 
        for(int j = 0; j < LENGTH; j++){
            State* state = new State(3);
            *state->id = rand() % 10000 + 1; //Debería insertar todos los elementos en un O(log(n)/1000) promedio
            *state->id1 = rand() % 10000 + 1;
            printf("%d %d\n", *state->id, *state->id1);
            int* zero = state->find(0);
            *state->i0 = zero[0];
            *state->j0 = zero[1];
            delete [] zero;
            state->calculateHeuristic();
            hash->push(*state->id, *state->id1);
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