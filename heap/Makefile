nothing:

test:
	gcc -c heap.c -o heap.o
	gcc -c hypercube.c -o hypercube.o
	gcc -c region.c -o region.o
	gcc hypercube.o region.o heap.o main.c -o main

run: test
	./main