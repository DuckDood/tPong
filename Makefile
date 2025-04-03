all: obj/main.o obj/border.o bin/pong

ifndef AI_SPEED
AI_SPEED = 0.2
endif

ifndef M_SPEED
M_SPEED = 2
endif

ifndef D_SPEED
D_SPEED = 0.5
endif

ifndef A_LEN
A_LEN = 3
endif

ifndef TICK_LEN
TICK_LEN = 20
endif

bin/pong: obj/main.o obj/border.o
	mkdir -p bin
	${CC} obj/main.o obj/border.o -lncurses -o bin/pong

obj/main.o: src/main.c
	mkdir -p obj
ifdef SMART_AI
	${CC} -c src/main.c -o obj/main.o -DSMART_AI -DA_SPEED=${AI_SPEED} -DM_SPEED=${M_SPEED} -DD_SPEED=${D_SPEED} -DA_LENIENCY=${A_LEN} -DTICK_LEN=${TICK_LEN}
else
	${CC} -c src/main.c -o obj/main.o -DA_SPEED=${AI_SPEED} -DM_SPEED=${M_SPEED} -DD_SPEED=${D_SPEED}
endif

obj/border.o: src/border.c
	mkdir -p obj
	${CC} -c src/border.c -o obj/border.o

clean:
	rm -r obj bin
