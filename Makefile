CC=gcc
CFLAGS=-Wall -Wpedantic -Wextra -std=c99

default: ./out/sport_db.o ./out/sport_events.o ./out/sport_athletes.o ./out/sport_registration.o
	gcc ./out/sport_db.o ./out/sport_events.o ./out/sport_athletes.o ./out/sport_registration.o -o sport

clean:
	rm -f -r ./out sport

./out/sport_db.o: ./src/sport_db.c ./src/sport_db.h
	mkdir -p out
	gcc -c ./src/sport_db.c -o ./out/sport_db.o

./out/sport_events.o: ./src/sport_events.c ./src/sport_events.h
	mkdir -p out
	gcc -c ./src/sport_events.c -o ./out/sport_events.o

./out/sport_athletes.o: ./src/sport_athletes.c ./src/sport_athletes.h
	mkdir -p out
	gcc -c ./src/sport_athletes.c -o ./out/sport_athletes.o

./out/sport_registration.o: ./src/sport_registration.c ./src/sport_registration.h
	mkdir -p out
	gcc -c ./src/sport_registration.c -o ./out/sport_registration.o