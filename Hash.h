#include "State.h"
struct Node {
    State* state;
    Node* next;
    Node(State* state){
        this->state = state;
        this->next = NULL;
    }
};
typedef struct Node Node;
class Hash {
private:
    Node* hashTable[100];
    int hashFunction(State* state);
public:
    Hash();
    ~Hash();
    void push(State* state);
    bool find(State* state);
    void clear();
    void print();
};