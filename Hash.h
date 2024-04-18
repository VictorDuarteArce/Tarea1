#include "AVL.h"
class Hash {
    private:
        AVL* hashTable[1000];
        int hashFunction(long unsigned int state);
    public:
        Hash();
        ~Hash();
        void push(long unsigned int state, long unsigned int state1);
        bool find(long unsigned int state, long unsigned int state1);
        void clear();
        void print();
};