#include "AVL.h"
#include <random>
int main() {
    AVL* avl = new AVL();

    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            avl->push(i, j);
        }
    }

    avl->print();

    /*for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 1000; j++){
            printf("%d", avl->find(1001, 1000));
        }
    }*/

    return 0;
}