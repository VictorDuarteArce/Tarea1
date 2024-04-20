#include "State.h"
State::State(){
    id = new long long unsigned int(0);
    id1 = new long long unsigned int(0);
    size = new int(0);
    i0 = new int(-1);
    j0 = new int(-1);
    heuristic = new float;
    distance = new int;
    misses = new int(-1);
    depth = new int;
    parent = nullptr;
}

State::State(int n){
    id = new long long unsigned int(0);
    id1 = new long long unsigned int(0);
    size = new int(n);
    i0 = new int(-1);
    j0 = new int(-1);
    heuristic = new float;
    distance = new int;
    misses = new int(-1);
    depth = new int;
    this->parent = nullptr;
}

State::State(int size, State *parent){
    id = new long long unsigned int(0);
    id1 = new long long unsigned int(0);
    this->size = new int(size);
    if(parent == nullptr){
        i0 = new int(-1);
        j0 = new int(-1);
    }else{
        i0 = new int(*parent->i0);
        j0 = new int(*parent->j0);
    }
    heuristic = new float;
    distance = new int;
    misses = new int(-1);
    depth = new int;
    this->parent = parent;
}
State::State(int size, State *parent, int **board) {
    id = new long long unsigned int;
    id1 = new long long unsigned int;
    this->size = new int(size);
    if(parent == nullptr){
        i0 = new int(-1);
        j0 = new int(-1);
    }else{
        i0 = new int(*parent->i0);
        j0 = new int(*parent->j0);
    }
    heuristic = new float;
    distance = new int;
    misses = new int(-1);
    depth = new int;
    this->setId(board);
    this->parent = parent;
}

State::~State() {
    delete id;
    delete size;
    delete i0;
    delete j0;
    delete heuristic;
    delete distance;
    delete misses;
    delete depth;
    parent = nullptr;
}

void State:: setId(int** board){
    *this->id = 0;
    *this->id1 = 0;
    int k = 0;
    int base = *this->size * *this->size;
    for(int i = 0; i < *this->size; i++){
        for(int j = 0; j < *this->size; j++){
            if(k < base / 2){ //estamos en la segunda mitad top-down left-right
                *this->id = *this->id * base + board[i][j];
            }else{ //estamos en la primera mitad top-down left-right
                *this->id1 = *this->id1 * base + board[i][j];
            }
            k++;
        }
    }
}

void State::print_board() {
    printf("Paso: %d\n", *this->depth);
    int**board = this->getBoard();
    for(int i = 0; i < *this->size; i++) {
        for(int j=0; j<*this->size; j++) {
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
    return *this->misses == 0;
}

State* State::copy() {
    State *new_state = new State(*this->size, this);
    *new_state->id = *this->id;
    *new_state->id1 = *this->id1;
    *new_state->heuristic = *this->heuristic;
    *new_state->distance = *this->distance;
    *new_state->misses = *this->misses;
    *new_state->depth = *this->depth;
    return new_state;
}

State * State::up() {
    if(*i0 != 0){ // si no esta en la primera fila entonces puedo subir el 0
        State *new_state = copy();
        int** board = this->getBoard();
        board[*i0][*j0] = board[*i0 - 1][*j0];
        board[*i0-1][*j0] = 0;
        *new_state->i0 = *new_state->i0 - 1;
        *new_state->depth = *this->depth + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < *size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateHeuristic();
        return new_state;
    }
    return(nullptr);
}

State * State::down() {
    if (*i0 != *size-1) { // si no esta en la ultima fila entonces puedo bajar el 0
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0]=board[*i0+1][*j0];
        board[*i0+1][*j0]=0;
        *new_state->i0 = *new_state->i0 + 1;
        *new_state->depth = *this->depth + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < *size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateHeuristic();
        return new_state;
    }
    return(nullptr);
}

State * State::right() {
    if (*j0 != *size - 1) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0] = board[*i0][*j0+1];
        board[*i0][*j0+1] = 0;
        *new_state->j0 = *new_state->j0 + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < *size; i++){
            delete [] board[i];
        }
        delete [] aux;        
        *new_state->depth = *this->depth + 1;
        new_state->calculateHeuristic();
        return new_state;
    }
    return(nullptr);
}

State * State::left() {
    if (*j0!=0) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0]=board[*i0][*j0-1];
        board[*i0][*j0-1]=0;
        *new_state->j0 = *new_state->j0 - 1;
        *new_state->depth = *this->depth + 1;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < *size; i++){
            delete [] board[i];
        }
        delete [] aux;
        new_state->calculateHeuristic();
        return new_state;
    }
    return(nullptr);
}
void State::calculateMisses(){
    int**board = this->getBoard();
    int value = 0;
    int k = 1;
    int base = *this->size * *this->size;
    for(int i = 0; i < *this->size; i++){
        for(int j = 0; j < *this->size; j++){
            if(board[i][j] != k % base){
                value++;
            }
            k++;
        }
    }
    *this->misses = value;
    int**aux = board;
    for(int i = 0; i < *size; i++){
        delete [] board[i];
    }
    delete [] aux;
}
void State::calculateDistance(){
    int value = 0;
    int k = 1;
    int** board = getBoard();
    for(int i = 0; i < *size; i++) {
        for(int j = 0; j < *size; j++) {
            if (board[i][j] != 0){
                int i2 = (board[i][j] - 1) / *size;
                int j2 = (board[i][j] - 1) % *size;
                *this->distance += abs(i - i2) + abs(j - j2);
            }
        }
    }
    *this->distance = value;
    for(int i = 0; i < *size; i++){
        delete [] board[i];
    }
    delete [] board;
}
int* State::find(int value){
    int**board = this->getBoard();
    int *pos = new int[2];
    for(int i = 0; i < *size; i++){
        for(int j = 0; j < *size; j++){
            if(board[i][j] == value){
                pos[0] = i;
                pos[1] = j;
                for (int k = 0; k < *size; k++) {
                    delete[] board[k];
                }
                delete[] board;
                return pos;
            }
        }
    }
    int**aux = board;
    for(int i = 0; i < *size; i++){
        delete [] board[i];
    }
    delete [] aux;
    return nullptr;
}
void State::calculateHeuristic(){
    this->calculateMisses();
    this->calculateDistance();
    if(*size > 4)
    *this->heuristic = 0.0182 * *depth/ *size + 0.1 * *distance/ *size + 0.12* *misses/ *size;
    else if(*size == 4)
    *this->heuristic = 0.0182 * *depth/ *size + *distance/ *size + 0.12* *misses / *size;
    else
    *this->heuristic = *depth;
}

int** State::getBoard(){
    long long unsigned int aux = *this->id;
    long long unsigned int aux1 = *this->id1;
    int **board = new int*[*this->size];
    for(int i = 0; i < *this->size; i++){
        board[i] = new int[*this->size];
    }
    int base = *this->size * *this->size;
    int k = 0;
    for(int i = *this->size - 1; i >= 0; i--){
        for(int j = *this->size - 1; j >= 0; j--){
            if(base % 2 != 0){ // Si el tamaño es impar
                if(k > base / 2){ // Si k es mayor a la mitad de la base
                    board[i][j] = *this->id % base;
                    *this->id = *this->id / base;
                }else{ // Si k es menor a la mitad de la base
                    board[i][j] = *this->id1 % base;
                    *this->id1 = *this->id1 / base;
                }
                k++;
            }else{ // Si el tamaño es par
                if(k >= base / 2){ // Si k es mayor o igual a la mitad de la base
                    board[i][j] = *this->id % base;
                    *this->id = *this->id / base;
                }else{ // Si k es menor a la mitad de la base
                    board[i][j] = *this->id1 % base;
                    *this->id1 = *this->id1 / base;
                }
                k++;
            }
        }
    }
    *this->id = aux;
    *this->id1 = aux1;
    return board;
}