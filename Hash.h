#include "State.h"
struct Node {
    long long unsigned int state_id;
    Node* next;
    Node(int state_id){
        this->state_id = state_id;
        this->next = NULL;
    }
};
typedef struct Node Node;
class Hash {
private:
    Node* hashTable[1000];
    int hashFunction(long long unsigned int state);
public:
    Hash();
    ~Hash();
    void push(long long unsigned int state);
    bool find(long long unsigned int state);
    void clear();
    void print();
};