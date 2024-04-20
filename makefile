FLAG ?= -g
all: State.o Puzzle.o Heap.o testState testPuzzle testHeap testAVL main 

State.o: State.cpp State.h
	g++ $(FLAG) -c State.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ $(FLAG) -c Puzzle.cpp

Heap.o: Heap.cpp Heap.h
	g++ $(FLAG) -c Heap.cpp

Hash.o: Hash.cpp Hash.h
	g++ $(FLAG) -c Hash.cpp

AVL.o: AVL.cpp AVL.h
	g++ $(FLAG) -c AVL.cpp

testState: testState.cpp State.o
	g++ $(FLAG) State.o testState.cpp -o testState

testHeap: testHeap.cpp Heap.o State.o
	g++ $(FLAG) Heap.o State.o testHeap.cpp -o testHeap

testPuzzle: testPuzzle.cpp Puzzle.o State.o
	g++ $(FLAG) State.o Puzzle.o testPuzzle.cpp -o testPuzzle

testHash: testHash.cpp Hash.o State.o AVL.o
	g++ $(FLAG) Hash.o State.o AVL.o testHash.cpp -o testHash

testAVL: testAVL.cpp AVL.o State.o
	g++ $(FLAG) AVL.o State.o testAVL.cpp -o testAVL
	
main: Puzzle.o State.o Hash.o Heap.o AVL.o main.cpp
	g++ $(FLAG) State.o Puzzle.o Hash.o Heap.o AVL.o main.cpp -o main

clear:
	rm -f *.o testState testPuzzle testHeap testHash main
