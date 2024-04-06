#include "AVL.h"

AVL::AVL() {
    root = nullptr;
}
AVL::~AVL() {
    clear(root);
}
void AVL::clear(NodeAVL *node) {
    if(node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
void AVL::push(State* state) {
    root = insert(root, state);
}
NodeAVL* AVL::insert(NodeAVL *node, State* state) {
    if(node == nullptr){
        node = new NodeAVL();
        node->state = state;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        node->balance = 0;
    } else if(state->value < node->state->value) {
        node->left = insert(node->left, state);
    } else if(state->value > node->state->value) {
        node->right = insert(node->right, state);
    }
    return balance(node);
}
void AVL::remove(State* state) {
    root = remove(root, state);
}
NodeAVL* AVL::remove(NodeAVL *node, State* state) {
    if(node == nullptr) {
        return nullptr;
    }
    if(state->value < node->state->value) {
        node->left = remove(node->left, state);
    } else if(state->value > node->state->value) {
        node->right = remove(node->right, state);
    } else {
        NodeAVL *left = node->left;
        NodeAVL *right = node->right;
        delete node;
        if(right == nullptr) {
            return left;
        }
        NodeAVL *min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}
NodeAVL* AVL::findMin(NodeAVL *node) {
    if(node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}
NodeAVL* AVL::removeMin(NodeAVL *node) {
    if(node->left == nullptr) {
        return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}
bool AVL::find(State* state) {
    return find(root, state) != nullptr;
}
NodeAVL* AVL::find(NodeAVL *node, State* state) {
    if(node == nullptr) {
        return nullptr;
    }
    if(state->value < node->state->value) {
        return find(node->left, state);
    } else if(state->value > node->state->value) {
        return find(node->right, state);
    }
    return node;
}
void AVL::print() {
    print(root);
    putchar('\n');
}
void AVL::print(NodeAVL *node) {
    if(node != nullptr) {
        print(node->left);
        printf("%d ", node->state->value);
        print(node->right);
    }
}
void AVL::update(NodeAVL *node) {
    int hl = (node->left == nullptr) ? 0 : node->left->height;
    int hr = (node->right == nullptr) ? 0 : node->right->height;
    node->height = 1 + ((hl > hr) ? hl : hr);
    node->balance = hr - hl;
}
NodeAVL* AVL::rotateLeft(NodeAVL *node) {
    NodeAVL *right = node->right;
    node->right = right->left;
    right->left = node;
    update(node);
    update(right);
    return right;
}
NodeAVL* AVL::rotateRight(NodeAVL *node) {
    NodeAVL *left = node->left;
    node->left = left->right;
    left->right = node;
    update(node);
    update(left);
    return left;
}
NodeAVL* AVL::balance(NodeAVL *node) {
    update(node);
    if(node->balance == -2) {
        if(node->left->balance == 1) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if(node->balance == 2) {
        if(node->right->balance == -1) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}
bool AVL::isEmpty() {
    return root == nullptr;
}
State* AVL::pop() {
    if(isEmpty()) {
        return nullptr;
    }
    NodeAVL *node = findMin(root);
    State *state = node->state;
    root = removeMin(root);
    return state;
}