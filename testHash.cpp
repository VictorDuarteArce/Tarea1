#include "Hash.h"
#include <random>

int main(){
    Hash* hash = new Hash();
    for(int i = 0; i < 1000; i++){
        State* state = new State();
        state->value = rand() % 1000;
        hash->push(state);
    }
    hash->print();
    for(int i = 0; i < 1000; i++){
        State* state = new State();
        state->value = rand() % 1000;
        printf("%d\n", hash->find(state));
        delete state;
    }
    return 0;
}