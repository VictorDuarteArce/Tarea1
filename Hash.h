#include "State.h"
struct Node {
    long int state_id;
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
    int hashFunction(long int state);
public:
    Hash();
    ~Hash();
    void push(long int state);
    bool find(long int state);
    void clear();
    void print();
};