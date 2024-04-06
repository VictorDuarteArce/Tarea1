#include "AVL.h"

int main(){
    AVL* avl = new AVL();
    for(int i = 0; i < 128; i++){
        State* state = new State();
        state->value = i;
        avl->push(state);
    }
    avl->print();
    return 0;
}