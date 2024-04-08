#include "State.h"

int main() {
    State *e = new State(5);
    e->id = 238471;
    e->generateBoard();
    e->print_board();
}