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
void Hash::push(long long unsigned int state){
    int index = hashFunction(state);
    if(hashTable[index] == NULL){
        hashTable[index] = new Node(state);
    }else{
        Node* current = hashTable[index];
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new Node(state);
    }
}
bool Hash::find(long long unsigned int state){
    int index = hashFunction(state);
    if(hashTable[index] != NULL){
        for(Node* current = hashTable[index]; current != NULL; current = current->next){
            if(current->state_id == state){
                return true;
            }
        }
    }
    return false;
}
int Hash::hashFunction(long long unsigned int state){
    return state % 1000;
}
void Hash::print(){
    for(int i = 0; i < 1000; i++){
        if(hashTable[i] != NULL){
            for(Node* current = hashTable[i]; current != NULL; current = current->next){
                printf("%llu ", current->state_id);
            }
            putchar('\n');
        }
    }
}