run: compile
	./bin/shellout.o
compile:
	gcc -o bin/shellout.o src/shellout.c src/commands/execution.c src/utils/command.c src/utils/list.c src/parser/parser.c src/history/history.c
