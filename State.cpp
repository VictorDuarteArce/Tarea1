#include "State.h"
State::State(){
    id = 0;
    size = 0;
    parent = nullptr;
}

State::State(int size) {
    this->size = size;
    id = 0;
    this->parent = nullptr;
}

State::State(int size, State *parent){
    this->size = size;
    this->id = 0;
    this->parent = parent;
}
State::State(int size, State *parent, int **board) {
    this->size = size;
    this->setId(board);
    this->parent = parent;
}

State::~State() {
    int size=0;
    parent = nullptr;
}

void State:: setId(int** board){
    this->id = 0;
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            this->id = this->id * this->size * this->size + board[i][j];
        }
    }
}

void State::print_board() {
    int**board = this->getBoard();
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void State::print() {
    if (parent != nullptr){
       parent->print();
    } 
    this->print_board();
    putchar('\n');
}

bool State::isSol() {
    return this->hits == this->size * this->size;
}

State* State::copy() {
    State *new_state = new State(size, this);
    new_state->id = this->id;
    new_state->i0 = this->i0;
    new_state->j0 = this->j0;
    new_state->value = this->value;
    new_state->distance = this->distance;
    new_state->hits = this->hits;
    new_state->level = this->level;
    return new_state;
}

State * State::up() {
    if(i0 != 0){ // si no esta en la primera fila entonces puedo subir el 0
        State *new_state = copy();
        int** board = this->getBoard();
        board[i0][j0] = board[i0-1][j0];
        board[i0-1][j0] = 0;
        new_state->i0--;
        new_state->level = this->level + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateValue();
        return new_state;
    }
    return(nullptr);
}

State * State::down() {
    if (i0!=size-1) { // si no esta en la ultima fila entonces puedo bajar el 0
        State *new_state = copy();
        int**board = this->getBoard();
        board[i0][j0]=board[i0+1][j0];
        board[i0+1][j0]=0;
        new_state->i0++;
        new_state->level = this->level + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateValue();
        return new_state;
    }
    return(nullptr);
}

State * State::right() {
    if (j0!=size-1) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[i0][j0]=board[i0][j0+1];
        board[i0][j0+1]=0;
        new_state->j0++;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < size; i++){
            delete [] board[i];
        }
        delete [] aux;        
        new_state->level = this->level + 1;        
        new_state->calculateValue();
        return new_state;
    }
    return(nullptr);
}

State * State::left() {
    if (j0!=0) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[i0][j0]=board[i0][j0-1];
        board[i0][j0-1]=0;
        new_state->j0--;        
        new_state->level = this->level + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateValue();
        return new_state;
    }
    return(nullptr);
}

bool State::equals(State *s) {
    return this->id == s->id;
}
void State::calculateHits(){
    int**board = this->getBoard();
    int value = 0;
    int k = 1;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int aux = k % (this->size * this->size);
            if(board[i][j] == aux){
                value++;
            }
            k++;
        }
    }
    this->hits = value;
    int**aux = board;
    for(int i = 0; i < size; i++){
        delete [] board[i];
    }
    delete [] aux;
}
void State::calculateDistance(){
    int value = 0;
    int k = 1;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int *aux = this->find(k % (this->size * this->size));
            value += (i - aux[0]) * (i - aux[0]) + (j - aux[1]) * (j - aux[1]);
            k++;this->value = 1 * level - hits;
            delete aux;
        }
    }
    this->distance = value;
}
int* State::find(int value){
    int**board = this->getBoard();
    int *pos = new int[2];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] == value){
                pos[0] = i;
                pos[1] = j;
                int**aux = board;
                for(int i = 0; i < size; i++){
                    delete [] board[i];
                }
                delete [] aux;
                return pos;
            }
        }
    }
    int**aux = board;
    for(int i = 0; i < size; i++){
        delete [] board[i];
    }
    delete [] aux;
    return nullptr;
}
void State::calculateValue(){
    this->calculateHits();
    this->calculateDistance();
    this->value = level;
}

int** State::getBoard(){
    long long unsigned int aux = this->id;
    int **board = new int*[this->size];
    for(int i = 0; i < this->size; i++){
        board[i] = new int[this->size];
    }
    int base = this->size * this->size;
    for(int i = this->size - 1; i >= 0; i--){
        for(int j = this->size - 1; j >= 0; j--){
            board[i][j] = this->id % base;
            this->id = this->id / base;
        }
    }
    this->id = aux;
    return board;
}