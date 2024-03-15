#NICOLAI Ilie - 313CB
build:
	gcc -g -o tema3 main.c task1.c freemem.c task2.c -std=c99 grafuri_gen.c lista.c
run:
	./tema3
clean:
	rm tema3
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3 -2