all: obj/main.o obj/border.o bin/pong

bin/pong: obj/main.o obj/border.o
	mkdir -p bin
	${CC} obj/main.o obj/border.o -lncurses -o bin/pong

obj/main.o: src/main.c
	mkdir -p obj
ifdef SMART_AI
ifdef AI_SPEED
	${CC} -c src/main.c -o obj/main.o -DSMART_AI -DA_SPEED=${AI_SPEED}
else
	${CC} -c src/main.c -o obj/main.o -DSMART_AI
endif
else
ifdef AI_SPEED
	${CC} -c src/main.c -o obj/main.o -DA_SPEED=${AI_SPEED}
else
	${CC} -c src/main.c -o obj/main.o
endif
endif

obj/border.o: src/border.c
	mkdir -p obj
	${CC} -c src/border.c -o obj/border.o

clean:
	rm -r obj bin
