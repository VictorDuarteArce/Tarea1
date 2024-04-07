#include "AVL.h"
#include <random>

int main(){
    AVL* avl = new AVL();
    for(int i = 0; i < 50; i++){
        State* state = new State();
        state->value = rand() % 1000;
        printf("Estado: %p, Valor: %d\n", state, state->value);
        avl->push(state);
    }
    for(int i = 0; avl->capacity > 0; i++){
        if(avl->states[i] != nullptr){
            printf("Null\n");
        }else{
            printf("Estado: %p, Valor: %d\n", avl->states[i], avl->states[i]->value);
        }
    }
    return 0;
}