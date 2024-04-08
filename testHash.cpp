#include "Hash.h"
#include <random>

int main(){
    Hash* hash = new Hash();
    for(int i = 0; i < 10000; i++){
        State* state = new State();
        state->id = rand() % 10000;
        hash->push(state->id);
    }
    hash->print();
    for(int i = 0; i < 10000; i++){
        State* state = new State();
        state->id = rand() % 10000;
        printf("%d\n", hash->find(state->id));
        delete state;
    }
    return 0;
}