#include "Stack.h"

int main() {
    Stack *s = new Stack(10);
    State *s1 = new State(3);
    int** board = new int*[3];
    for(int i = 0; i < 3; i++){
        board[i] = new int[3];
    }
    int contador = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = contador % (3*3);
            contador++;
        }
    }
    s1->board = board;
    s->push(s1);
    s->push(s1);
    s->push(s1);
    State *s2 = s->pop();
    s2->print();
    s2 = s->pop();
    s2->print();
    s2 = s->pop();
    s2->print();
    return 0;
}