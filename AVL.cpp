#include "AVL.h"

AVL::AVL(){
    root = nullptr;
}
AVL::~AVL(){
    clear(root);
}
void AVL::clear(NodeAVL *node){
    if(node){
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
int AVL::getHeight(NodeAVL *node){
    if(node == nullptr)
        return 0;
    return node->height;
}
int AVL::getBalance(NodeAVL *node){
    if(node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

NodeAVL* AVL::rightRotate(NodeAVL* node){
    if (node == nullptr || node->left == nullptr)
        return node; // No se puede rotar si el nodo o su hijo izquierdo es nulo

    NodeAVL* newRoot = node->left;
    NodeAVL* temp = newRoot->right;

    // Perform rotation
    newRoot->right = node;
    node->left = temp;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    // Return new root
    return newRoot;
}

NodeAVL* AVL::leftRotate(NodeAVL* node){
    if (node == nullptr || node->right == nullptr)
        return node; // No se puede rotar si el nodo o su hijo derecho es nulo

    NodeAVL* newRoot = node->right;
    NodeAVL* temp = newRoot->left;

    // Perform rotation
    newRoot->left = node;
    node->right = temp;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    // Return new root
    return newRoot;
}


int AVL::max(int a, int b){
    return (a > b)? a : b;
}

void AVL::push(long long unsigned int id, long long unsigned int id1){
    root = push(root, id, id1);
}

NodeAVL* AVL::push(NodeAVL* node, long long unsigned int id, long long unsigned int id1){
    if(node == nullptr)
        return new NodeAVL(id, id1);

    if(id < node->id)
        node->left = push(node->left, id, id1);
    else if(id > node->id)
        node->right = push(node->right, id, id1);
    else{
        if(id1 < node->id1)
            node->left = push(node->left, id, id1);
        else if(id1 > node->id1)
            node->right = push(node->right, id, id1);
        return node;
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && id < node->left->id)
        return rightRotate(node);
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void AVL::inOrder(){
    inOrder(root);
    std::cout << std::endl;
}
void AVL::inOrder(NodeAVL *node){
    if(node != nullptr){
        inOrder(node->left);
        printf("%llu %llu\n", node->id, node->id1);
        inOrder(node->right);
    }
}

void AVL::preOrder(){
    preOrder(root);
    std::cout << std::endl;
}
void AVL::preOrder(NodeAVL *node){
    if(node != nullptr){
        printf("%llu %llu\n", node->id, node->id1);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void AVL::postOrder(){
    postOrder(root);
    std::cout << std::endl;
}
void AVL::postOrder(NodeAVL *node){
    if(node != nullptr){
        postOrder(node->left);
        postOrder(node->right);
        printf("%llu %llu\n", node->id, node->id1);
    }
}

bool AVL::find(long long unsigned int id, long long unsigned int id1){
    return find(root, id, id1);
}

bool AVL::find(NodeAVL *node, long long unsigned int id, long long unsigned int id1){
    if(node == nullptr)
        return false;
    if(node->id == id && node->id1 == id1)
        return true;
    if(id < node->id)
        return find(node->left, id, id1);
    if(id > node->id)
        return find(node->right, id, id1);
    if(id1 < node->id1)
        return find(node->left, id, id1);
    if(id1 > node->id1)
        return find(node->right, id, id1);
    return false;
}

void AVL::print(){
    print(root);
    std::cout << std::endl;
}

void AVL::print(NodeAVL *node){
    if(node != nullptr){
        print(node->left);
        printf("(%llu,%llu) ", node->id, node->id1);
        print(node->right);
    }
}