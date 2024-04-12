#include "Hash.h"
#include <random>

int main(){
    Hash* hash = new Hash();
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            State* state = new State(3);
            state->id = rand() % 10000 + 1;
            state->id1 = rand() % 10000 + 1;
            state->calculateHeuristic();
            state->i0 = state->find(0)[0];
            state->j0 = state->find(0)[1];
            hash->push(state->id, state->id1);
        }
    }
    hash->print();
    /*for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            State* state = new State();
            state->id = i;
            state->id1 = j;
            printf("%d", hash->find(state->id, state->id1));
            delete state;
        }
    }*/
    return 0;
}