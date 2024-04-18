#include "State.h"
State::State(){
    id = (long unsigned int*)malloc(sizeof(long unsigned int));
    size = (int*)malloc(sizeof(int));
    i0 = (int*)malloc(sizeof(int));
    j0 = (int*)malloc(sizeof(int));
    heuristic = (float*)malloc(sizeof(float));
    distance = (int*)malloc(sizeof(int));
    hits = (int*)malloc(sizeof(int));
    depth = (int*)malloc(sizeof(int));
    *id = 0;
    *size = 0;
    parent = nullptr;
}

State::State(int n) {
    *size = n;
    *id = 0;
    this->parent = nullptr;
}

State::State(int size, State *parent){
    *this->size = size;
    *this->id = 0;
    this->parent = parent;
}
State::State(int size, State *parent, int **board) {
    *this->size = size;
    this->setId(board);
    this->parent = parent;
}

State::~State() {
    free(id);
    free(size);
    free(i0);
    free(j0);
    free(heuristic);
    free(distance);
    free(hits);
    free(depth);
    parent = nullptr;
}

void State:: setId(int** board){
    *this->id = 0;
    *this->id1 = 0;
    int k = 0;
    for(int i = 0; i < *this->size; i++){
        for(int j = 0; j < *this->size; j++){
            if(k < (*this->size * *this->size) / 2){
                *this->id = *this->id * *this->size * *this->size + board[i][j];
            }else{
                *this->id1 = *this->id1 * *this->size * *this->size + board[i][j];
            }
            k++;
        }
    }
}

void State::print_board() {
    printf("Paso: %d\n", *this->depth);
    int**board = this->getBoard();
    for(int i = 0; i < *size; i++) {
        for(int j=0; j<*size; j++) {
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
    return *this->hits == *this->size * *this->size;
}

State* State::copy() {
    State *new_state = new State(*this->size, this);
    new_state->id = this->id;
    new_state->id1 = this->id1;
    new_state->i0 = this->i0;
    new_state->j0 = this->j0;
    new_state->heuristic = this->heuristic;
    new_state->distance = this->distance;
    new_state->hits = this->hits;
    new_state->depth = this->depth;
    return new_state;
}

State * State::up() {
    if(i0 != 0){ // si no esta en la primera fila entonces puedo subir el 0
        State *new_state = copy();
        int** board = this->getBoard();
        board[*i0][*j0] = board[*i0-1][*j0];
        board[*i0-1][*j0] = 0;
        new_state->i0--;
        new_state->depth = this->depth + 1;
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
    if (i0!=size-1) { // si no esta en la ultima fila entonces puedo bajar el 0
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0]=board[*i0+1][*j0];
        board[*i0+1][*j0]=0;
        new_state->i0++;
        new_state->depth = this->depth + 1;
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
    if (j0!=size-1) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0]=board[*i0][*j0+1];
        board[*i0][*j0+1]=0;
        new_state->j0++;
        new_state->setId(board);
        int**aux = board;
        for(int i = 0; i < *size; i++){
            delete [] board[i];
        }
        delete [] aux;        
        new_state->depth = this->depth + 1;        
        new_state->calculateHeuristic();
        return new_state;
    }
    return(nullptr);
}

State * State::left() {
    if (j0!=0) {
        State *new_state = copy();
        int**board = this->getBoard();
        board[*i0][*j0]=board[*i0][*j0-1];
        board[*i0][*j0-1]=0;
        *new_state->j0--;        
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

bool State::equals(State *s) {
    return *this->id == *s->id;
}
void State::calculateHits(){
    int**board = this->getBoard();
    int value = 0;
    int k = 1;
    for(int i = 0; i < *size; i++) {
        for(int j = 0; j < *size; j++) {
            int aux = k % (*this->size * *this->size);
            if(board[i][j] == aux){
                value++;
            }
            k++;
        }
    }
    *this->hits = value;
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
                int i2=(board[i][j]-1)/ *size;
                int j2=(board[i][j]-1)% *size;
                distance+=abs(i-i2)+abs(j-j2);
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
                int**aux = board;
                for(int i = 0; i < *size; i++){
                    delete [] board[i];
                }
                delete [] aux;
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
    this->calculateHits();
    this->calculateDistance();
    if(*size > 4)
    this->heuristic = 0.0182* *depth/ *size + 0.1 * *distance/ *size + 0.12*(size - hits)/ *size;
    else if(size == 4)
    this->heuristic = 0.0182*depth/size + distance/size + 0.12*(size - hits)/size;
    else
    this->heuristic = depth;
}

int** State::getBoard(){
    long long unsigned int aux = this->id;
    long long unsigned int aux1 = this->id1;
    int **board = new int*[this->size];
    for(int i = 0; i < this->size; i++){
        board[i] = new int[this->size];
    }
    int base = this->size * this->size;
    int k = 0;
    for(int i = this->size - 1; i >= 0; i--){
        for(int j = this->size - 1; j >= 0; j--){
            if(this->size % 2){
                if(k > this->size * this->size / 2){
                    board[i][j] = this->id % base;
                    this->id = this->id / base;
                }else{
                    board[i][j] = this->id1 % base;
                    this->id1 = this->id1 / base;
                }
                k++;
            }else{
                if(k >= this->size * this->size / 2){
                    board[i][j] = this->id % base;
                    this->id = this->id / base;
                }else{
                    board[i][j] = this->id1 % base;
                    this->id1 = this->id1 / base;
                }
                k++;
            }
        }
    }
    this->id = aux;
    this->id1 = aux1;
    return board;
}