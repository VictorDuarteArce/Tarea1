#include "State.h"

struct NodeAVL {
    State* state;
    NodeAVL *left;
    NodeAVL *right;
    int height;
    int balance;
};

class AVL{
    public:
        AVL();
        ~AVL();
        void push(State* state);
        void remove(State* state);
        State* pop();
        bool find(State* state);
        void print();
        bool isEmpty();
    private:
        NodeAVL *root;
        NodeAVL* insert(NodeAVL *node, State* state);
        NodeAVL* remove(NodeAVL *node, State* state);
        NodeAVL* find(NodeAVL *node, State* state);
        void print(NodeAVL *node);
        void update(NodeAVL *node);
        NodeAVL* rotateLeft(NodeAVL *node);
        NodeAVL* rotateRight(NodeAVL *node);
        NodeAVL* balance(NodeAVL *node);
        NodeAVL* removeMin(NodeAVL *node);
        NodeAVL* findMin(NodeAVL *node);
        void clear(NodeAVL *node);
};

