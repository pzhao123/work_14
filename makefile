all: main.c
	gcc -o signal main.c

run: 
	./signal

clear:
	rm "msg.txt"