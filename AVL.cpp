#include "AVL.h"

AVL::AVL(){
    this->capacity = 0;
    this->states = nullptr;
}
AVL::~AVL(){
    delete[] this->states;
}
State* AVL::goLeft(int index){
    return this->states[2*index+1];
}
State* AVL::goRight(int index){
    return this->states[2*index+2];
}
void AVL::push(State* state){
    pushHelper(state, 0);
}
void AVL::pushHelper(State* state, int index){
    if(this->capacity == 0){
        this->states = new State*[1];
        this->states[0] = state;
        this->capacity = 1;
        return;
    }
    while(index >= this->capacity){
        printf("a ");
        State** temp = new State*[this->capacity+1];
        for(int i = 0; i < this->capacity; i++){
            temp[i] = this->states[i];
        }
        delete[] this->states;
        this->states = temp;
        this->capacity++;
    }
    if(this->states[index] == nullptr){
        printf("Encontramos espacio\n");
        this->states[index] = state;
        return;
    }
    if(state->value < this->states[index]->value){
        pushHelper(state, 2*index+1);
    }else{
        pushHelper(state, 2*index+2);
    }
}
bool AVL::find(State* state){
    return findHelper(this->states, state, 0);
}
bool AVL::findHelper(State** temp, State* state, int index){
    if(temp[index] == nullptr){
        return false;
    }
    if(temp[index]->value == state->value){
        return true;
    }
    if(state->value < temp[index]->value){
        return findHelper(temp, state, 2*index+1);
    }else{
        return findHelper(temp, state, 2*index+2);
    }
}
void AVL::print(){
    printf("Printing Preorder\n");
    printPreOrder();
    printf("Printing Inorder\n");
    printInOrder();
    printf("Printing Postorder\n");
    printPostOrder();
    printf("Printing Level by Level\n");
    printLevelByLevel();
}
void AVL::printPreOrder(){
    printPreOrderHelper(this->states, 0);
}
void AVL::printPreOrderHelper(State** temp, int index){
    if(temp[index] == nullptr){
        return;
    }
    printf("%d\n", temp[index]->value);
    printPreOrderHelper(temp, 2*index+1);
    printPreOrderHelper(temp, 2*index+2);
}
void AVL::printInOrder(){
    printInOrderHelper(this->states, 0);
}
void AVL::printInOrderHelper(State** temp, int index){
    if(temp[index] == nullptr){
        return;
    }
    printInOrderHelper(temp, 2*index+1);
    printf("%d\n", temp[index]->value);
    printInOrderHelper(temp, 2*index+2);
}
void AVL::printPostOrder(){
    printPostOrderHelper(this->states, 0);
}
void AVL::printPostOrderHelper(State** temp, int index){
    if(temp[index] == nullptr){
        return;
    }
    printPostOrderHelper(temp, 2*index+1);
    printPostOrderHelper(temp, 2*index+2);
    printf("%d\n", temp[index]->value);
}
void AVL::printLevelByLevel(){
    printLevelByLevelHelper(this->states, 0, 0);
}
void AVL::printLevelByLevelHelper(State** temp, int index, int level){
    if(temp[index] == nullptr){
        return;
    }
    printLevelByLevelHelper(temp, 2*index+1, level+1);
    printf("Level %d: %d\n", level, temp[index]->value);
    printLevelByLevelHelper(temp, 2*index+2, level+1);
}