#include "State.h"
class AVL{
    public:
        State** states;
        int capacity;
        AVL();
        ~AVL();
        State* goLeft(int index);
        State* goRight(int index);
        void push(State* state);
        void pushHelper(State* state, int index);
        bool find(State* state);
        bool findHelper(State** temp, State* state, int index);
        //void balance();
        void print();
        void printPreOrder();
        void printPreOrderHelper(State** temp, int index);
        void printInOrder();
        void printInOrderHelper(State** temp, int index);
        void printPostOrder();
        void printPostOrderHelper(State** temp, int index);
        void printLevelByLevel();
        void printLevelByLevelHelper(State** temp, int index, int level);
};