#include "State.h"

struct NodeAVL{
    long long unsigned int id;
    long long unsigned int id1;
    NodeAVL *left, *right;
    int height;
    NodeAVL(long long unsigned int id, long long unsigned int id1){
        this->id = id;
        this->id1 = id1;
        left = right = nullptr;
        height = 1;
    }
};

class AVL{
    public:
        NodeAVL *root;
        AVL();
        ~AVL();
        void clear(NodeAVL *node);
        int getHeight(NodeAVL *node);
        int getBalance(NodeAVL *node);
        NodeAVL* rightRotate(NodeAVL *y);
        NodeAVL* leftRotate(NodeAVL *x);
        int max(int x, int y);
        NodeAVL* push(NodeAVL *node, long long unsigned int id, long long unsigned int id1);
        void balance(NodeAVL *node);
        void push(long long unsigned int id, long long unsigned int id1);
        void preOrder(NodeAVL *node);
        void preOrder();
        void inOrder(NodeAVL *node);
        void inOrder();
        void postOrder(NodeAVL *node);
        void postOrder(); 
        bool find(NodeAVL *node, long long unsigned int id, long long unsigned int id1);
        bool find(long long unsigned int id, long long unsigned int id1);
        void print(NodeAVL *node);
        void print();
};