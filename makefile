all: State.o Stack.o Puzzle.o Heap.o testState testStack testPuzzle testHeap main 

State.o: State.cpp State.h
	g++ -g -c State.cpp

Stack.o: Stack.cpp Stack.h
	g++ -g -c Stack.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

AVL.o: AVL.cpp AVL.h
	g++ -g -c AVL.cpp

Hash.o: Hash.cpp Hash.h
	g++ -g -c Hash.cpp

testState: testState.cpp State.o
	g++ -g State.o testState.cpp -o testState

testStack: testStack.cpp Stack.o State.o
	g++ -g State.o Stack.o testStack.cpp -o testStack

testHeap: testHeap.cpp Heap.o State.o
	g++ -g Heap.o State.o testHeap.cpp -o testHeap

testPuzzle: testPuzzle.cpp Puzzle.o State.o Stack.o AVL.o
	g++ -g State.o Stack.o Puzzle.o AVL.o testPuzzle.cpp -o testPuzzle

testAVL: testAVL.cpp AVL.o State.o
	g++ -g AVL.o State.o testAVL.cpp -o testAVL

testHash: testHash.cpp Hash.o State.o
	g++ -g Hash.o State.o testHash.cpp -o testHash

main: Puzzle.o State.o Stack.o Hash.o main.cpp
	g++ -g State.o Stack.o Puzzle.o Hash.o main.cpp -o main

clear:
	rm -f *.o testState testStack testPuzzle testHeap testAVL testHash main
