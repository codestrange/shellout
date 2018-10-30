run: compile
	./bin/shellout.o
compile:
	gcc -o bin/shellout src/shellout.c src/commands/execution.c
