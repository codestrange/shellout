run: compile
	./bin/shellout.o
compile:
	gcc -o bin/shellout.o src/shellout.c
