all: pipes.c
	gcc -o pipes pipes.c
run: all
	./pipes
