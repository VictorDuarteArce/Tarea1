#include "Hash.h"

Hash::Hash(){
    for(int i = 0; i < 1000; i++){
        hashTable[i] = NULL;
    }
}
Hash::~Hash(){
    clear();
}
void Hash::clear(){
    for(int i = 0; i < 1000; i++){
        if(hashTable[i] != NULL){
            delete hashTable[i];
            hashTable[i] = NULL;
        }
    }
}
void Hash::push(long unsigned int state, long unsigned int state1){
    int index = hashFunction(state);
    if(hashTable[index] == NULL){
        hashTable[index] = new AVL();
    }
    hashTable[index]->push(state, state1);
}
bool Hash::find(long unsigned int state, long unsigned int state1){
    int index = hashFunction(state);
    if(hashTable[index] == NULL){
        return false;
    }
    return hashTable[index]->find(state, state1);
}
int Hash::hashFunction(long unsigned int state){
    return state % 1000;
}
void Hash::print(){
    for(int i = 0; i < 1000; i++){
        if(hashTable[i] != NULL){
            hashTable[i]->print();
        }
    }
}