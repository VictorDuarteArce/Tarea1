#include "AVL.h"
class Hash {
    private:
        AVL* hashTable[1000];
        int hashFunction(long long unsigned int state);
    public:
        Hash();
        ~Hash();
        void push(long long unsigned int state, long long unsigned int state1);
        bool find(long long unsigned int state, long long unsigned int state1);
        void clear();
        void print();
};