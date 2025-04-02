all: obj/main.o obj/border.o bin/pong

bin/pong: obj/main.o obj/border.o
	mkdir -p bin
	gcc obj/main.o obj/border.o -lncurses -o bin/pong

obj/main.o: src/main.c
	mkdir -p obj
	gcc -c src/main.c -o obj/main.o 	

obj/border.o: src/border.c
	mkdir -p obj
	gcc -c src/border.c -o obj/border.o
