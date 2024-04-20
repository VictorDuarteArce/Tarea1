#include "AVL.h"
#include <random>
#define LENGTH 10
int main(){ //El objetivo de este test es probar la estructura AVL
    AVL* avl = new AVL();

    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < LENGTH; j++){
            avl->push(i, j); //Debería insertar todos los elementos en un O(log(n)) promedio
        }
    }

    avl->print();

    for(int i = 0; i < LENGTH; i++){
        for(int j = 0; j < LENGTH; j++){
            printf("%d", avl->find(i, j)); //Debería imprimir 1, encuentra todos los elementos en un O(log(n)) promedio
        }
    }

    return 0;
}